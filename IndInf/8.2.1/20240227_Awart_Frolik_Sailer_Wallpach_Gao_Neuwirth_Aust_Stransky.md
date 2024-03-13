# 8.2.1 Industrielle Handhabungssysteme "Externe Signale und Gerätekommunikation"

## Ziele
Die Ziele der Übung "Externe Signale und Gerätekommunikation" umfassen das Verständnis des IO-Boards sowie den Austausch von Daten zwischen dem Kuka-Roboter und dem Schaltboard. Der Roboter soll in der Lage sein, Eingänge auszulesen und Ausgänge anzusteuern. Die Steuerung soll abhängig von den Eingängen und der Position des Roboter-Greifarms die Ausgänge schalten, um Bauteile vom Fließband zu bewegen.

Wir verfügen über Inputs und Outputs:
- Wir steuern die Ventile für die Druckluft, um das Fließband zu bewegen.
- Zusätzlich gibt es zwei Tasten, eine Wahlschaltung und eine Signallampe.
- Die Zylinder sind mit Positionssensoren ausgestattet, die rückmelden, ob sie ausgefahren oder nicht ausgefahren sind.
- Der Motor des Förderbands ist ebenfalls ein Output (zusätzlich abgesichert mit einem Not-Halt nur für den Motor, wiederanlaufgeschützt).

Es gibt insgesamt 8 Bauteile an 8 unterschiedlichen Positionen. Das Programm soll folgende Funktionen umfassen:

## Herausforderungen
1. Sinnvollen Ablauf überlegen.
2. Applikation selbst gestalten (Dialogfeld).
3. Eingaben (JOptionPane), die vom Nutzer kommen, verarbeiten (I/Os ansprechen).
4. "Das gemeine ä"

## Tätigkeiten der Gruppe
- Werkzeug am Kuka Roboter anbringen: Der Sauger am Adapter des Werkzeugwechslers am Kuka Roboter musste angebracht werden.

Lösungsansätze:
- Flussdiagramm erstellen.
- Code schreiben.
- Testen.

## Flussdiagramm
1. Acht Bauteile liegen auf der Palette (die Palette befindet sich wartend in der Ausgangsposition).
2. Benutzer wählt im Interface (Eingabefeld/Dialogfeld über die Steuerkonsole) ein Bauteil anhand der ID (=Position) aus.
3. Verhindern, dass eine neue Bestellung aufgegeben wird.
4. (Optional) Manuellmodus - manueller Override (Förderband fahren/stoppen mittels Schalter).
5. Roboter sendet eine Anforderung "Ich brauche eine Palette".
6. Förderband einschalten.
7. Palette fährt über das Fließband auf die Position.
8. Endschalter sind relevant.
9. Palette spannen.
10. Palette sendet Bestätigung an den Roboter "Palette auf Position" (Meldung für den Benutzer).
11. Mit dem Greifarm über die Palette fahren und positionieren.
12. Bucht öffnen.
13. Entnehmen.
14. Roboter greift Bauteil von der gewünschten Position.
15. Roboter fährt zur Box.
16. Roboter lässt Bauteil los und wirft es somit in eine Box.
17. Meldung "Bauteil abgeliefert".
18. Eingabefeld für Bestellung freigeben (Lampe leuchtet grün).

![Flussdiagramm](assets/Flussdiagramm.jpeg)

## Kommentierter Programmcode
Code in Kuka Robot Language (KRL) wird noch hinzugefügt.

```KRL

```

## Aufgetretene Probleme & daraus resultierende Erkenntnisse
1. Sauger funktioniert nicht weil falscher Schlauch angesteckt. Aktivierung nicht über Taste sondern über I/O.
2. 

## Fotos

## Fragestellungen
1. Was versteht man unter "normally open" und "normally closed", wenn man von einem Taster spricht?
   - Normally Open (NO) und Normally Closed (NC) beschreiben den Standardzustand eines Tasters oder Schalters. Ein NO-Taster schließt den Stromkreis, wenn er gedrückt wird, während ein NC-Taster den Stromkreis im Ruhezustand schließt und beim Drücken öffnet.

2. Wie kann man Taster mit Eingangsmodulen verbinden?
   - Taster können direkt mit den Eingangsmodulen des IO-Boards verbunden werden, indem man die entsprechenden NO- oder NC-Kontakte nutzt.

3. Wie kann man LEDs oder Lampen mit Ausgangsmodulen verbinden?
   - Um LEDs mit den Ausgangsmodulen zu verbinden, können die Eingänge der Ausgangsmodule mit den entsprechenden Kontakten der LEDs oder Lampen verbunden werden.

4. Mit welchen Programmkonstrukten kann ein Greifer geöffnet und geschlossen werden?
   - Das Öffnen und Schließen eines Greifers kann über digitale Ausgangssignale gesteuert werden.

5. Wie können Ausgänge gesetzt werden?
   - Ausgänge können mit den Befehlen `OUT` oder `SET` gesetzt werden.

6. Wie können Eingänge ausgelesen werden?
   - Eingänge werden mit dem Befehl `IN` ausgelesen, um den Zustand von Sensoren oder Tastern zu überprüfen.

7. Mit welchem Programmkonstrukt kann auf das Setzen eines Einganges gewartet werden?
   - Um auf ein spezifisches Eingangssignal zu warten, kann das Konstrukt `WAIT FOR` verwendet werden. Dies ermöglicht dem Programm, die Ausführung zu pausieren, bis ein bestimmter Eingangszustand erkannt wird.


## Code

### Input Prompt
```
DECL KrlMsg_T Message 
DECL KrlMsgPar_T Parameter[3] 
DECL KrlMsgOpt_T Opt 
DECL KrlMsgDlgSK_T Key[7] 
DECL INT Ticket, Answer

Message = {Modul[]“USER”, Nr 1508, Msg_txt[]“Teil auswählen”} 
Key[1]= {SK_type #value, SK_txt[]“Teil 1”} 
Key[2]= {SK_type #value, SK_txt[]"Teil 2"}
Key[3]= {SK_type #value, SK_txt[]"Teil 3"} 
Key[4]= {SK_type #value, SK_txt[]"Teil 4"} 
Key[5]= {SK_type #value, SK_txt[]"Teil 5"} 
Key[6]= {SK_type #value, SK_txt[]"Teil 6"} 
Key[7]= {SK_type #value, SK_txt[]"Teil 7"} 
Key[8]= {SK_type #value, SK_txt[]"Teil 8"} 
Key[9]= {SK_type #empty} 

Opt = {VL_Stop TRUE, Clear_P_Reset TRUE, Clear_P_SAW TRUE, Log_To_DB FALSE} 

Ticket = Set_KrlDlg(Message, Parameter[],Key[], Opt)


IF (Ticket > 0) THEN 
    WHILE (Exists_KrlDlg (Ticket, Answer)) 
        WAIT SEC 0 
    ENDWHILE 
    SWITCH Answer 
        CASE 1 
            //Methode um Teil 1 auszuwählen
        CASE 2
            //Methode um Teil 2 auszuwählen
        CASE 3
            //Methode um Teil 3 auszuwählen
        ...
    ENDSWITCH 
ENDIF 
```


![WhatsApp Image 2024-03-12 at 08.47.03 -1-](assets/WhatsApp%20Image%202024-03-12%20at%2008.47.03%20-1-.jpeg)

![WhatsApp Image 2024-03-12 at 08.47.03 -3-](assets/WhatsApp%20Image%202024-03-12%20at%2008.47.03%20-3-.jpeg)
![WhatsApp Image 2024-03-12 at 08.47.03](assets/WhatsApp%20Image%202024-03-12%20at%2008.47.03.jpeg)
