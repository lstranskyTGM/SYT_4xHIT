# [GK] 8.4.1 Systemsicherheit "Firewall"

Verfasser: **Leonhard Stransky, 4AHIT**

Datum: **21.02.2024**

## Einführung

Diese Übung zeigt die Absicherung eines Netzwerks bzw. eines Servers mittels einer Firewall.

## Ziele

Das Ziel dieser Übung ist die Absicherung eines Servers sowie eines Netzwerk-Segments mit einer stateful Firewall.

## Vorraussetzungen

- Netzwerkkonfiguration und Netzwerk-Grundbefehle unter Linux
- statisches Routing unter Linux
- 2 virtuelle Maschinen mit Linux (GUI nicht notwendig, Distribution wahlweise) - Server und Router

## Aufgaben

Konfiguriere die beiden virtuellen Maschinen wie folgt:

Server Eine Netzwerkschnittstelle:

(eth0, Internes Netzwerk), IP-Adresse 192.168.KatNr.10/24
Router Zwei Netzwerkschnittstellen:

(eth0, Internes Netzwerk), IP-Adresse 192.168.KatNr.1/24
(eth1, Netzwerkbrücke), IP-Adresse über DHCP
(ANMERKUNG: statt ethX sind je nach Distribution die entsprechenden ensXX Schnittstellen zu verwenden)

### Task 1 - Absicherung des Servers

a) Installiere auf dem System einen SSH-Server sowie einen Webserver (nginx, apache, ...).

b) Konfiguriere eine stateful Firewall auf dem System (iptables, nft, ...) so, dass

- externer Zugriff nur auf SSH, HTTP und HTTPS erlaubt ist,
- der Server Netzwerk-Troubleshooting (ping, traceroute, nslookup, ...) durchführen kann,
(ANMERKUNG: zum Testen ist der Server mit dem Internet zu verbinden - entweder durch Task 2 oder durch verwenden einer Passenden VM-Netzwerkeinstellung)

### Task 2 - Routing, Port-Forwarding und NAT

a) Aktiviere ip-forwarding auf dem Router und teste die Funktion.

b) Konfiguriere die Port-Weiterleitung (DNAT) wie folgt:

- eth1:80 -> 192.168.KatNr.10:80
- eth1:443 -> 192.168.KatNr.10:443
- eth1:2222 -> 192.168.KatNr.10:22

## Umsetzung

### Server Configuration

```bash
## Securing the Server
## (Commands)
# Update & Upgrade Packages
sudo apt-get update 
sudo apt-get upgrade -y
# Install SSH Server (If not in Setup)
sudo apt-get install openssh-server -y
# Install Web Server
sudo apt-get install apache2 -y
# Configure Stateful Firewall
sudo ufw enable
sudo ufw allow ssh
sudo allow http
sudo allow https
# Installing nftables
sudo apt install nftables
# Start and Enable nftables
sudo systemctl enable nftables
# Create Configuration
sudo nano /etc/nftables.conf
# Load Configuration
sudo nft flush ruleset
sudo nft -f /etc/nftables.conf
# Verify Configuration
sudo nft list ruleset
```

```conf
#!/usr/sbin/nft -f

flush ruleset

table inet filter {
    chain input {
        type filter hook input priority 0;

        # Accept any localhost traffic
        iif "lo" accept

        # Accept traffic originated from us
        ct state established,related accept

        # Allow ICMP for network troubleshooting, without rate limiting for simplicity
        ip protocol icmp accept
        ip6 nexthdr icmpv6 accept

        # Accept SSH, HTTP, and HTTPS
        tcp dport { 22, 80, 443 } accept

        # Drop everything else not explicitly allowed
        counter drop
    }

    chain output {
        type filter hook output priority 0;
        policy accept; # Allow all outgoing traffic
    }

    chain forward {
        type filter hook forward priority 0;
        policy drop; # Drop all forwarded traffic by default
    }
}
```

```bash
# Create Network Configuration Files
cd /etc/systemd/network/
sudo nano 10-static-enp0s3.network
# Enable and Start systemd-networkd
sudo systemctl enable systemd-networkd
sudo systemctl start systemd-networkd
# Verify Configuration
ip addr show enp0s3
ifconfig -a
```

```ini
[Match]
Name=enp0s3

[Network]
Address=192.168.19.10/24
Gateway=192.168.19.1
DNS=8.8.8.8
DNS=8.8.4.4
```

```bash
# Disabeling nft (Overkill ufw is enough)
sudo systemctl stop nftables
# Changing netplan configuration
sudo nano /etc/netplan/01-netcfg.yaml
# Apply Changes
sudo netplan apply
```

```yaml
network:
    ethernets:
        ens33:
            addresses:
            - 192.168.19.10/24
            gateway4: 192.168.2.1
            nameserver:
                addresses: []
                search: []
    version: 2
```

### Router Configuration

```bash
# Update & Upgrade Packages
sudo apt-get update 
sudo apt-get upgrade -y
# Install SSH Server (If not in Setup)
sudo apt-get install openssh-server -y
# Enable IP Forwarding
echo "net.ipv4.ip_forward=1" | sudo tee -a /etc/sysctl.conf
# Apply changes by running
sudo sysctl -



# Create Network Configuration Files
iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to-destination 192.168.KatNr.10
```

```yaml
network:
    ethernets:
        ens37:
            dhcp4: false
            dhcp4-overrides:
                use-routes: false
            addresses:
            - 192.168.19.1/24
            # gateway4: 192.168.2.1
            nameservers:
                addresses: []
                search: []
        ens33:
            dhcp4: true
    version: 2
```

## Summary

### Stateful vs. Stateless Firewalls

#### Stateful Firewalls

Stateful firewalls track the state of active connections and make decisions based on the context of the traffic. They remember the connection's state (e.g., TCP streams or UDP communication) and allow or block traffic based on the history of the connection. This enables more granular control, distinguishing between new, established, and existing connections.

- Advantage: More secure by understanding connection context.
- Use case: Dynamic, complex network environments.

#### Stateless Firewalls

Stateless firewalls filter traffic solely based on source and destination addresses, ports, and protocol used without considering the connection state. Each packet is processed in isolation, which can be faster but potentially less secure.

- Advantage: Faster processing by treating each packet individually.
- Use case: Simple filtering needs where speed is a priority.

### How to Secure a Firewall

Securing a firewall involves defining rules that specify allowed and blocked traffic. Below are guidelines using iptables, nftables, and ufw.

#### Using iptables

Set Default Policies: Drop all incoming and forwarding traffic by default; allow all outgoing.

```bash
sudo iptables -P INPUT DROP
sudo iptables -P FORWARD DROP
sudo iptables -P OUTPUT ACCEPT
```

Allow Specific Traffic: Only allow traffic on necessary ports or for established connections.

```bash
sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT  # SSH
```

#### Using nftables

Create a Table and Chains: Define input, forward, and output chains with a policy to drop or accept traffic as needed.

```nft
table inet filter {
    chain input {
        type filter hook input priority 0; policy drop;
        ct state established,related accept
        tcp dport 22 accept  # SSH
    }
    chain forward {
        policy drop;
    }
    chain output {
        policy accept;
    }
}
```

Apply the Configuration: Load the nftables rules.

```bash
sudo nft -f /path/to/your_ruleset.nft
```

#### Using UFW (Uncomplicated Firewall)

Enable UFW and Set Default Policies: Deny incoming connections by default and allow outgoing.

```bash
sudo ufw enable
sudo ufw default deny incoming
sudo ufw default allow outgoing
```

Allow Specific Ports: Permit traffic on necessary ports.

```bash
sudo ufw allow ssh
sudo ufw allow http
sudo ufw allow https
```

### Other Security Measures

- Update Firewall Rules Regularly: Keep rules current to meet security policies and protect against threats.
- Limit Access: Restrict firewall configuration access to authorized personnel.
- Logging and Monitoring: Enable logging to monitor suspicious activities.
- Test Your Firewall: Regularly verify your firewall's effectiveness and rule accuracy.

## Bewertung

Grundanforderungen überwiegend erfüllt
- [ ] Task 1 - Absicherung des Servers

Grundanforderungen zur Gänze erfüllt
- [ ] Task 2 - Routing, Port-Forwarding und NAT


## Quellen

[1] https://www.lanner-america.com/blog/stateless-vs-stateful-packet-filtering-firewalls-better/

### iptables

[2] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

[3] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

[4] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

[5] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

### nft (netfilter)

[6] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

[7] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/

[8] https://www.ionos.at/digitalguide/server/tools/iptables-tutorial-regelwerk-fuer-datenpakete-erstellen/