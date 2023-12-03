# INDINF_7.1

Verfasser: **Leonhard Stransky, 4AHIT**

Datum: **03.10.2023**

## Einführung

Roboter sind IT-Systeme, die mit der Welt physikalisch interagieren. Die Programmierung unterscheidet sich in vielen Punkten von der klassischen "Applikationsentwicklung", da hier Problemfelder wie Sicherheit (im Sinne körperlicher Sicherheit, Verletzungsvermeidung, ...) und verlässlicher Betrieb in Zusammenarbeit mit vielen verschiedenen Geräten und Komponenten in Spiel kommen.

Diese Übung soll einen kleinen Einblick in diese spannende Welt geben, um "Awareness" für eine mögliche zukünftige Zusammenarbeit mit Mechatronikern und Automatisierung zu schaffen - und um einmal mit den coolen Spielzeugen hantieren zu dürfen

## Projektbeschreibung

In dieser Übung soll vor allem praktisch mit dem Roboter gearbeitet werden. Notiere dabei aber dennoch, wie du deine Aufgaben umgesetzt hast, um dies später (im 2. Semester) ohne nochmalige Erklärungen umsetzen zu können.
Seine Arbeit informativ, übersichtlich und effizient protokollieren zu können, ist ein wesentlicher Skill eines Ingenieurs, der auch in dieser Übung geübt werden soll.

## Projektteam:

- Julian Neuwirth
- Duchon Kevin
- Bakshi Pavel

## Aufgaben:

### Teil 1 (GK):

#### Aufgabenstellung:

Befestige die Schablone "Layout 4" (Format A3, Farbe) im Arbeitsbereich des Roboters.

Setze 3 Würfel auf die Plätzen 1, 2 und 3. Anschließend setze mithilfe des Roboters die Würfel folgendermaßen um:

Schüler 1: 1-->4, 2-->4 (Würfel 2 horizonal greifen)
Schüler 2: 2-->5, 3-->5 (Würfel 3 horizonal greifen)
Schüler 3: 3-->4, 2-->5 (Würfel 2 horizonal greifen)
Schüler 4: 1-->5, 3-->5 (Würfel 2 horizonal greifen)

Beim horizontalen Greifen ACHTUNG auf den Abstand zwischen Roboterarm und Tisch!

Vermiss die durch das blaue Koordinatenkreuz gegebene Basis und speichere die Konfiguration unter Basis Nummer 10. Verwende dazu das bereits vermessene Werkzeug "LISE0 Greifer" (Nummer 2)

Wiederhole die Bewegungen aus 2. Welche Verbesserungen ergeben sich durch Benutzung des Basiskoordinatensystems beim Umsetzen der Würfel?

#### Ablauf:

Unser erster Versuch im Team verlief nicht wie geplant. Der Roboterarm bewegte sich zu schnell und stieß abrupt gegen den Tisch, wodurch einige Teile des Lego Greifarms weggeschleudert wurden. Diese konnte man aber ohne Probleme wieder montieren.

Als Schüler 4 hatte ich keine Schwierigkeiten, den Roboter zu steuern. Ich setzte die Würfel 1 und 3 auf die Plätze 5 und 4 um.

Jedoch wurde das Steuern des Roboters erheblich erleichtert, als wir ein kalibriertes Koordinatensystem verwendeten.

Hierfür mussten wir den Roboter zu den Fixpunkten fahren und die Koordinaten eintragen.

Bereits zuvor war ein Koordinatensystem auf der Arbeitsfläche makriert. Dadurch war es einfacher, die Koordinaten Punkte festzulegen.

### Teil 2 (GK):

#### Aufgabenstellung:

Nun sollen die Bewegungen in automatisch ablaufende Programme umgesetzt werden. Damit nach jedem Schülerteil die Würfel wieder in die Ausgangslage gelegt werden können, soll jeweils eine 3 Sekunden Pause programmiert werden.

Erstelle ein neues Modul mit den Name aller Schüler (ev. abgekürzt)

Programmiere die Bewegungsabläufe: "Teache" alle erforderlichen Bewegungspunkte. Überlege, welche Punkte sich für mehrere Bewegungen nutzen lassen und verwende sie wieder (nicht die selbe Koordinate in mehrere Variablen speichern). Benenne alle Punkte nachvollziehbar!
Achte darauf, den Greifer nicht schon während der Bewegung zu öffnen bzw. zu schließen, sondern erst bei Stillstand des Roboters.

Verwende für Wege zwischen Würfelpositionen Point-to-Point-Bewegungen, für das Greifen der Würfel Linearbewegungen.

Teste das Programm ausführlich.

#### Ablauf:

Beim erstellen des Programms war es manchmal etwas schwierig die richtigen Commands zu finden. Sonst war es mit viel Experimentieren verbunden. Zum Beispiel wo man die Points platzieren soll usw.

Jedoch war es aufgrund der Zeit nicht möglich das Programm zu vollenden.

Ich denke das wir uns alle aber dennoch intesiv mit dem Roboter auseinandersetzen konnten. 

## Quellen:

[1] www.elearning.tgm.ac.at 2023. [online] 
Available at: https://elearning.tgm.ac.at/mod/assign/view.php?id=78435 [Accessed 06 Oktober 2023].














