# INDINF_7.1

Verfasser: **Leonhard Stransky, 4AHIT**

Datum: **03.10.2023**

## Voraussetzungen:

Im 3. Jahrgang hast du schon Kontakt mit einem Industrieroboter gehabt. Dabei sollten folgende
Ziele erreicht worden sein:
- Du hast die Sicherheitseinweisung am spezifischen Roboter mitgemacht.
- Du kannst den Roboter grundlegend in Betrieb nehmen und einfache Meldungen des
Systems bearbeiten.
- Du kannst alle Achsen des Roboters benennen und per Handbediengerät bewegen.
- Du kennst die Bewegungseinschränkungen und Limits aller Achsen und kannst den TCP
gezielt an einen Punkt im Raum steue

## Ziele:

- Du kennst die verschiedenen Koordinatensysteme, die bei Roboterbewegungen eingesetzt
werden, und die Gründe dafür.
- Du kannst eigene Werkzeug- und Basis-Koordinatensysteme definieren und
Roboterbewegungen sinnvoll einsetzen.
- Du kannst ein einfaches Programm zum Abfahren eines Pfades schreiben, ausführen und
testen.

## Projektteam:

- Julian Neuwirth
- Duchon Kevin
- Bakshi Pavel

## Aufgaben:

### Teil 1 (GK):

#### Aufgabenstellung:

Schüler 1: 1-->4, 2-->4 (Würfel 2 horizonal greifen)
Schüler 2: 2-->5, 3-->5 (Würfel 3 horizonal greifen)
Schüler 3: 3-->4, 2-->5 (Würfel 2 horizonal greifen)
Schüler 4: 1-->5, 3-->5 (Würfel 2 horizonal greifen)

Vermiss die durch das blaue Koordinatenkreuz gegebene Basis und speichere die Konfiguration unter Basis Nummer 10. Verwende dazu das bereits vermessene Werkzeug "LISE0 Greifer" (Nummer 2)

Wiederhole die Bewegungen aus 2. Welche Verbesserungen ergeben sich durch Benutzung des Basiskoordinatensystems beim Umsetzen der Würfel?

#### Ablauf:

Unser erster Teamversuch verlief nicht ganz nach Plan. Der Roboterarm bewegte sich zu schnell und stieß unerwartet gegen den Tisch. Das führte dazu, dass einige Teile des Lego Greifarms weggeschleudert wurden. Aber diese Teile ließen sich problemlos wieder montieren, sodass wir unsere Arbeit fortsetzen konnten.

Als Schüler 4 in unserer Gruppe hatte ich die Aufgabe, die Würfel 1 und 3 umzusetzen. Ich positionierte Würfel 1 auf Platz 5 und Würfel 3 auf Platz 5. Dabei hatte ich die Schwierigtkeit, dass ich aus der Perspektive vom Roboter steuern musste. Ansonsten lief alles andere einwandfrei.

##### Vermessung und Konfiguration des Koordinatensystems:

Die Nutzung eines kalibrierten Koordinatensystems führte zu einer deutlichen Verbesserung bei der Steuerung des Roboters. Wir navigierten den Roboter zu definierten Fixpunkten, um die Koordinaten einzugeben, was sich als effektiv erwies.

Das Vorhandensein eines Koordinatensystems auf der Arbeitsfläche erleichterte das Festlegen der Koordinatenpunkte und trug zu präziseren und effizienteren Roboterbewegungen bei.

### Teil 2 (GK):

#### Aufgabenstellung:

1. Erstelle ein neues Modul mit den Name aller Schüler (ev. abgekürzt)

2. Programmiere die Bewegungsabläufe: "Teache" alle erforderlichen Bewegungspunkte.
Überlege, welche Punkte sich für mehrere Bewegungen nutzen lassen und verwende sie
wieder (nicht die selbe Koordinate in mehrere Variablen speichern). Benenne alle Punkte
nachvollziehbar!
Achte darauf, den Greifer nicht schon während der Bewegung zu öffnen bzw. zu schließen,
sondern erst bei Stillstand des Roboters.

3. Verwende für Wege zwischen Würfelpositionen Point-to-Point-Bewegungen, für das Greifen
der Würfel Linearbewegungen.

4. Teste das Programm ausführlich.

#### Ablauf:

Beim Programmieren des Roboters mussten wir oft experimentieren, besonders um die richtigen Befehle herauszufinden. Anfangs war es nicht immer einfach, aber mit der Zeit kamen wir besser zurecht. Die Herausforderung bestand darin, die Punkte zu finden, an denen der Roboter stoppen sollte.

Leider reichte die Zeit nicht aus, um das Programm komplett fertigzustellen. Wir konnten nur einen Teil der geplanten Funktionen implementieren.

Trotzdem haben wir viel über den Umgang mit dem Roboter gelernt. Für jeden Punkt, den der Roboter ansteuern sollte, haben wir zuerst manuell mit dem Steuerungsstick die Position eingestellt. So konnte der Roboterarm später genau diese Punkte anfahren. 

### Abschlussworte:

Im Rückblick war dieses Robotik-Projekt eine interessante Herausforderung. Wir haben uns intensiv mit der Programmierung und Steuerung des Roboters auseinandergesetzt. Trotz der Zeitbeschränkungen konnten wir einige wichtige Aspekte in der Praxis umsetzen. Es war eine gute Gelegenheit, mit dem Team zu arbeiten und gemeinsam an Lösungen zu tüfteln.

## Verbesserung der Abgabe:

- Entfernen bzw. Kürzen der Angaben 
- Ausformulierung bzw. Erweiterung des Textes
- Abschlussworte hinzugefügt
- Alle Quellen aufgelistet

## Quellen:

[1] www.elearning.tgm.ac.at 2023. [online] 
Available at: [Basisvermessung.pdf](https://elearning.tgm.ac.at/pluginfile.php/109713/mod_assign/introattachment/0/Basisvermessung.pdf?forcedownload=1) [Accessed 06 Oktober 2023].

[2] www.elearning.tgm.ac.at 2023. [online] 
Available at: [Dokumentation Kuka.pdf](https://elearning.tgm.ac.at/pluginfile.php/109713/mod_assign/introattachment/0/Dokumentation%20Kuka.pdf?forcedownload=1) [Accessed 06 Oktober 2023].

[3] www.elearning.tgm.ac.at 2023. [online] 
Available at: [KRL_Cheatsheet.pdf](https://elearning.tgm.ac.at/pluginfile.php/109713/mod_assign/introattachment/0/KRL_Cheatsheet.pdf?forcedownload=1) [Accessed 06 Oktober 2023].

[4] www.elearning.tgm.ac.at 2023. [online] 
Available at: [KUKA KRL-Quickguide.pdf](https://elearning.tgm.ac.at/pluginfile.php/109713/mod_assign/introattachment/0/KUKA%20KRL-Quickguide.pdf?forcedownload=1) [Accessed 06 Oktober 2023].

[5] www.elearning.tgm.ac.at 2023. [online] 
Available at: [SYT-Lab Layout 4.pdf](https://elearning.tgm.ac.at/pluginfile.php/109713/mod_assign/introattachment/0/SYT-Lab%20Layout%204.pdf?forcedownload=1) [Accessed 06 Oktober 2023].










