# En partant de la racine de projet:
make
./build/prog

# Controles
z: deplacement sur z negatif
s: deplacement sur z positif
q: deplacement sur x negatif
d: deplacement sur x positif
a: deplacement sur y negatif
e: deplacement sur y positif
espace: activer la poussé verticale
click & hold lmb: bouger la camera
click & hold rmb: orientatin du lem par poussées rotatives, ces controles sont assimilés a un manche d'avion:
  click a gauche de la fenetre: rotation a droite (yaw)
  click a droite de la fenetre: rotation a gauche (yaw)
  click en haute de la fenetre: rotation en avant (pitch)
  click en bas de la fenetre: rotation en arriere (pitch)
scroll: zoom
u: toggle minimap
p: pause
r: redemarrer
f: affichage debug (coordonnées & fps)
v: toggle model editor
h: toggle GL_DEPTH_TEST
H: toggle GL_CULL_FACE
l: toggle GL_LIGHTING
L: toggle GL_COLOR_MATERIAL
o: changer entre GL_FILL, GL_LINE, GL_POINT
O: changer entre (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), GL_DEPTH_BUFFER_BIT, GL_COLOR_BUFFER_BIT
