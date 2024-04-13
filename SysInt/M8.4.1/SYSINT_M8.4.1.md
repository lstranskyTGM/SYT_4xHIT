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

## Implementation

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

`nftables` Configuration:
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


`systemd-networkd` Configuration:
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

`netplan` Configuration:
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

`netplan` Configuration: (Version 2)
```yaml
network:
  version: 2
  ethernets:
    enp0s3:
      dhcp4: no
      addresses: [192.168.19.10/24]
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
sudo sysctl -p
# Create Network Configuration Files
sudo iptables -t nat -A PREROUTING -i enp0s8 -p tcp --dport 80 -j DNAT --to-destination 192.168.19.10:80
sudo iptables -t nat -A PREROUTING -i enp0s8 -p tcp --dport 443 -j DNAT --to-destination 192.168.19.10:443
sudo iptables -t nat -A PREROUTING -i enp0s8 -p tcp --dport 2222 -j DNAT --to-destination 192.168.19.10:22
```

`netplan` Configuration:
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

`netplan` Configuration: (Version 2)
```yaml
network:
  version: 2
  ethernets:
    enp0s3:  # Internal Interface
      dhcp4: no
      addresses: [192.168.19.1/24]
    enp0s8:  # External Interface (bridge)
      dhcp4: true
```

## Testing

### 1. Verify iptables Configuration

```bash
sudo iptables -t nat -L PREROUTING -v -n
```

- [X] works as expected

### 2. SSH Connection Test (Router to Server)

```bash
ssh -p 22 192.168.19.10
```

- [X] works as expected

### 3. External SSH Connection Test

```bash
ssh -p 2222 external-ip-of-router
```

- [ ] works as expected

## Problems

### 1. Network Adapter Configuration

- `nftables` configuration did not work
- `netplan` configuration did not work

#### Changed VM network configuration

1. Server:
    - Adapter 1: Internes Netzwerk
2. Router:
    - Adapter 1: Internes Netzwerk
    - Adapter 2: Netzwerkbrücke

### 2. External SSH Connection

- `ssh -p 2222 external-ip-of-router` did not work

#### Check Firewall Settings & Port Forwarding

```bash
# Check using verbose mode
ssh -vvv -p 2222 external-ip-of-router
```

```plaintext
OpenSSH_for_Windows_8.6p1, LibreSSL 3.4.3
debug3: Failed to open file:C:/Users/Leonhard/.ssh/config error:2
debug3: Failed to open file:C:/ProgramData/ssh/ssh_config error:2
debug2: resolve_canonicalize: hostname 192.168.200.70 is address
debug3: expanded UserKnownHostsFile '~/.ssh/known_hosts' -> 'C:\\Users\\Leonhard/.ssh/known_hosts'
debug3: expanded UserKnownHostsFile '~/.ssh/known_hosts2' -> 'C:\\Users\\Leonhard/.ssh/known_hosts2'
debug1: Authenticator provider $SSH_SK_PROVIDER did not resolve; disabling
debug3: ssh_connect_direct: entering
debug1: Connecting to 192.168.200.70 [192.168.200.70] port 2222.
debug3: finish_connect - ERROR: async io completed with error: 10060, io:000001E0A0BCBD90
debug1: connect to address 192.168.200.70 port 2222: Connection timed out
ssh: connect to host 192.168.200.70 port 2222: Connection timed out
```

```bash
# Log Check on Server
sudo cat /var/log/auth.log | grep sshd
```

```plaintext
Apr 13 19:54:28 mail sshd[3288]: pam_unix(sshd:auth): authentication failure; logname= uid=0 euid=0 tty=ssh ruser= rhost=192.168.19.1  user=user
Apr 13 19:54:31 mail sshd[3288]: Failed password for user from 192.168.19.1 port 45366 ssh2
Apr 13 19:54:33 mail sshd[3288]: Accepted password for user from 192.168.19.1 port 45366 ssh2
Apr 13 19:54:33 mail sshd[3288]: pam_unix(sshd:session): session opened for user user(uid=1000) by (uid=0)
Apr 13 19:54:36 mail sshd[3347]: Received disconnect from 192.168.19.1 port 45366:11: disconnected by user
Apr 13 19:54:36 mail sshd[3347]: Disconnected from user user 192.168.19.1 port 45366
Apr 13 19:54:36 mail sshd[3288]: pam_unix(sshd:session): session closed for user user
Apr 13 20:19:09 mail sshd[4093]: Accepted password for user from 192.168.19.1 port 36740 ssh2
Apr 13 20:19:09 mail sshd[4093]: pam_unix(sshd:session): session opened for user user(uid=1000) by (uid=0)
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
- [X] Task 1 - Absicherung des Servers

Grundanforderungen zur Gänze erfüllt
- [X] Task 2 - Routing, Port-Forwarding und NAT


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