print("demarrage du script")
squelette = lua.Monstre()
joueur = lua.Entite()

pos = lua.vec(3, 3)

print("squelette deplacer a : ")
pos:afficher()

squelette:deplacer(pos:getVecteur())

print("squelette deplacer2")




