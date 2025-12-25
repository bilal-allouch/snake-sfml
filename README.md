# 🐍 Snake SFML

Un jeu **Snake classique** développé en **C++ (C++17)** avec **SFML**, conçu autour d’une **architecture orientée objet claire** et d’une **séparation nette entre la logique du jeu et l’affichage graphique**.

Ce projet met l’accent sur la **qualité du code**, la **modularité** et la **maintenabilité**, en respectant de bonnes pratiques d’ingénierie logicielle.

---

## ✨ Fonctionnalités

* États du jeu : **Démarrage**, **Pause**, **En jeu**, **Fin de partie**
* Déplacement fluide du serpent via le clavier
* Détection des collisions avec les murs et avec le corps du serpent
* Apparition de la nourriture uniquement sur des cases libres
* Croissance du serpent et système de score
* Augmentation progressive de la difficulté selon le score
* Affichage propre basé sur une grille
* Messages visuels (Démarrer, Pause, Game Over)

---

## 🎮 Commandes

* **Flèches directionnelles** : déplacer le serpent
* **ESPACE** : démarrer la partie / rejouer
* **P** : mettre en pause / reprendre
* **R** : redémarrer la partie
* **ESC** : quitter le jeu

---

## 🛠️ Compilation et exécution

### Prérequis

* Linux ou WSL (Ubuntu)
* Compilateur compatible **C++17**
* **SFML 2.5+**
* **CMake 3.16+**

### Installation des dépendances

```bash
sudo apt update
sudo apt install -y g++ cmake libsfml-dev
```

### Compilation

```bash
cmake -S . -B build
cmake --build build
```

### Exécution

```bash
./build/snake
```

---

## 📁 Structure du projet

```
assets/
  fonts/          Polices utilisées dans le jeu

docs/
  diagrams/       Diagrammes UML (Mermaid)

include/
  core/           En-têtes de la logique du jeu
  graphics/       En-têtes du rendu graphique

src/
  core/           Implémentation de la logique du jeu
  graphics/       Implémentation du rendu graphique
```

---

## 🧠 Architecture et conception

Le projet est organisé autour de responsabilités bien définies :

**Game**
Gère la boucle principale, la machine à états, les entrées clavier et les mises à jour du jeu.

**Snake**
Contrôle le déplacement, la croissance et la détection des collisions du serpent.

**Food**
Représente la position de la nourriture et sa logique de réapparition.

**Renderer**
S’occupe exclusivement de l’affichage : grille, serpent, nourriture et messages UI.

---

## 📐 Diagrammes

Le projet inclut plusieurs diagrammes UML réalisés avec **Mermaid** afin de documenter l’architecture et le fonctionnement :

* **Diagramme de classes**
  `docs/diagrams/class_diagram.mmd`

* **Diagramme de séquence (boucle de jeu)**
  `docs/diagrams/sequence_game_loop.mmd`

* **Diagramme d’états**
  `docs/diagrams/state_machine.mmd`

---

## 🧩 Notes de développement

* Développement progressif avec des commits Git fréquents et significatifs
* Architecture pensée pour être facilement extensible
* Priorité donnée à la lisibilité et à la maintenabilité du code

---

## 🚀 Améliorations futures

* Effets sonores et musique de fond
* Menu principal avec paramètres
* Sauvegarde du meilleur score
* Tailles de plateau et modes de difficulté différents
* Serpent contrôlé par une IA simple

---

## 👤 Auteur

**Bilal Allouch**
