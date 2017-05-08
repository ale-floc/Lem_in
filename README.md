# Lem_in

Ce projet de l'école 42, à réaliser seul, est un projet d'algorithme ayant pour but de trouver le chemin le plus court d'une map pour ramener X fourmis d'un point A à un point B.

![alt text](header.png)

## install & usage

~~~sh
git clone https://github.com/kaboff/Lem_in.git ~/Lem_in
cd ~/Lem_in && make
~~~

~~~sh
./lem_in [-e] < [maps]
~~~

## notice

Analyse d'une maps
  > 5 <- nombre de fourmis
  
  > salle1 x y <- le nom de la salle suivis de sont point X et Y
  
  > ##start <- la prochaine salle valide sera la salle de depart de la fourmilieres
  
  > ##end <- la prochaine salle valide sera la fin de la fourmilieres
  
  > #commentaires <- un commentaires
  
  > salle1-salle2 <- relie la salle1 a la salle2
