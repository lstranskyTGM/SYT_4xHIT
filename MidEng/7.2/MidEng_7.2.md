# MidEng_7.2

Verfasser: **Leonhard Stransky, 4AHIT**

Datum: **28.11.2023**

## Einführung

Diese Übung soll die Funktionsweise und Implementierung von eine Message Oriented Middleware (MOM) mit Hilfe des Frameworks Apache Active MQ demonstrieren. Message Oriented Middleware (MOM) ist neben InterProcessCommunication (IPC), Remote Objects (RMI) und Remote Procedure Call (RPC) eine weitere Möglichkeit um eine Kommunikation zwischen mehreren Rechnern umzusetzen.

Die Umsetzung basiert auf einem praxisnahen Beispiel eines Lagerstandorts. Die Zentrale der Handelskette KONSUM moechte einmal pro Tag die aktuellen Lagerbestaende jedes Standortes abfragen.

Mit diesem Ziel soll die REST-Applikation aus MidEng 7.1 Warehouse REST and Dataformats bei einem entsprechenden Request http:///warehouse/sendData die Daten (JSON oder XML) in eine Message Queue der Zentral uebertragen. In regelmaessigen Abstaenden werden alle Message Queues der Zentrale abgefragt und die Daten aller Standorte gesammelt.

Diese Daten werden dann erneut ueber eine REST-Schnittstelle in XML oder JSON zur Verfuegung gestellt.

## Projektbeschreibung

Das Ziel dieser Übung ist die Implementierung einer Kommunikationsplattform für eine Handelskette. Dabei erfolgt ein Datenaustausch von mehreren Lagerstandorten mit der Zentrale unter Verwendung einer Message Oriented Middleware (MOM). Die einzelnen Daten des Lagerstandortes sollen an die Zentrale übertragen werden. Es sollen nachrichtenbasierten Protokolle mit Message Queues verwendet werden. Durch diese lose Kopplung kann gewährleistet werden, dass in Zukunft weitere Anlagen hinzugefügt bzw. Kooperationspartner eingebunden werden können.

Fuer die REST-Schnittstelle in der Zentralle muessen die Datenstrukturen der einzelnene Standorte zusammengefasst werden. Um die Datenintegrität zu garantieren, sollen jene Daten, die mit der Middleware übertragen werden in einer LOG-Datei abgespeichert werden.

## Aufgaben:

MOMSender:
```java
    // Parameter für die Verbindung
    private static String user = ActiveMQConnection.DEFAULT_USER;
    private static String password = ActiveMQConnection.DEFAULT_PASSWORD;
    private static String url = ActiveMQConnection.DEFAULT_BROKER_URL;
    private static String subject = "windengine_001";
    // 


## Quellen:

[1] www.Test1.com 2023. *Test1* [online] 
Available at: https://www.Test1.com/wiki/Test1 [Accessed 18 March 2023].

[2] www.Test2.com 2023. *Test2* [online] 
Available at: https://www.Test2.com/wiki/Test2 [Accessed 18 March 2023].

[3] www.Test3.com 2023. *Test3* [online] 
Available at: https://www.Test3.com/wiki/Test3 [Accessed 18 March 2023].

[4] www.Test4.com 2023. *Test4* [online] 
Available at: https://www.Test4.com/wiki/Test4 [Accessed 18 March 2023].












