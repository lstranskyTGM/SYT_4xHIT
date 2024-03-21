# [GK] 8.3.1 Kommunikationsdienste - E-Mail

Verfasser: **Leonhard Stransky, 4AHIT**

Datum: **19.02.2024**

## Einführung

In dieser Übung sollen unternehmensweite (textbasierte) Kommunikationsmittel installiert und betrieben werden.

## Ziele

Ziel dieser Übung ist es eine Übersicht über ein E-Mail-System zu bekommen.

## Vorrausetzungen

- Grundlagen Linux und DNS
- Virtualisierungsumgebung Ubuntu 20.04 LTS (unter 22.04 kann es zu Problemen kommen)

## Aufgaben

Installiere und konfiguriere den Mail-Server iRedMail. Das Versenden und Empfangen von Mails muss funktionieren - dazu musst du auch entsprechende Domains/Hostnamen konfigurieren (entweder über DNS oder über die Hosts-Datei).
Achtung: Du musst für diese Übung keine Domain kaufen. Die Übung wird lokal in einer virtuellen Maschine durchgeführt.

## Umsetzung

Erstellen der virtuellen Maschine mit UbuntuServer 20.04 LTS

Portweiterleitung für Port 22, 80 und 443

Putty für SSH Verbindung

Update und Upgrade der Pakete
```bash
sudo apt update
sudo apt upgrade -y
```

Hostname erstellen
```bash
sudo hostnamectl set-hostname mail.your-domain.com
```

Updaten der /etc/hosts Datei
```bash
sudo nano /etc/hosts
```

Dateiinhalt:
```plaintext
127.0.0.1       mail.your-domain.com localhost
```

Änderungen überprüfen
```bash
sudo hostname -f
```

Mail Server aufsetzen
```bash
# Download iRedMail
wget https://github.com/iredmail/iRedMail/archive/1.5.0.tar.gz
# Entpacken
tar xvf 1.5.0.tar.gz
# Wechseln in das Verzeichnis
cd iRedMail-1.5.0/
# Ausführungs Rechte geben
chmod +x iRedMail.sh
# Starten des Scripts
sudo bash iRedMail.sh
```

System neustarten
```bash
sudo reboot
```

Nach Installation des Mail-Servers und der Konfiguration der Domains/Hostnamen, kann man über
**127.0.0.1/mail** das Webinterface erreichen.

Auf der Admin Seite kann man einen neuen Benutzer anlegen und diesem eine E-Mail-Adresse zuweisen.
**127.0.0.1/iredadmin**

Diese User/Mail adressen habe ich für die Übung angelegt:
```plaintext
postmaster@your-domain.com
pw: test
user1@your-domain.com
pw: 123456A!
```

## Probleme

SMTP Error beim Versenden von Mails, da ein Service nicht automatisch gestartet wurde

Dieser Fehler konnte durch das Starten des Services behoben werden

```bash
sudo systemctl start [Service-Name] (z.B. postfix)
```

## Bewertung

Grundanforderungen überwiegend erfüllt
- [X] Installation des Mail-Servers
  
Grundanforderungen vollständig erfüllt
- [X] Versenden und Empfangen von E-Mails funktioniert

## Quellen:

[1] https://www.linuxbabe.com/mail-server/ubuntu-20-04-iredmail-server-installation

[2] https://ubuntu.com/download/server














