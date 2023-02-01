# R2.08-TP2-Detection-de-mouvement-dans-les-videos

## Requirements

- OpenCV 4.6.0

## Paramètrage du projet sous Visual Studio 2022

- Il faut modifier le répertoire include d'OpenCV en fonction d'où il se trouve sur votre PC
<img width="504" alt="image" src="https://user-images.githubusercontent.com/42523430/215989766-44d6679f-5d71-4e97-a3d2-54d5b1eb3b01.png">

- Il faut indiquer le répertoire de librairies additionnelles comme sur l'image ci-dessous
<img width="743" alt="image" src="https://user-images.githubusercontent.com/42523430/215990279-aa741dc1-1c89-4731-b18a-b29f5602fcc4.png">

- Si vous utilisez une autre version d'OpenCV que celle recommandée au début du README, il faudra changer la librairie comme ci-après
<img width="589" alt="image" src="https://user-images.githubusercontent.com/42523430/215990709-019a8c11-d978-4883-9fc0-456c7b34339a.png">
Si vous utilisez par exemple la version 4.5.5, il faut remplacer *opencv_world460d.lib* par *opencv_world455d.lib*

## Fichiers à ajouter pour le bon fonctionnement d'OpenCV

- Ajouter le fichier "opencv_world460d.dll" situé dans "opencv\build\x64\vc15\bin" au niveau de l'exécutable de l'application
- Ajouter le fichier "opencv_videoio_ffmpeg460_64.dll" situé dans "opencv\build\bin" au niveau de l'exécutable de l'application
