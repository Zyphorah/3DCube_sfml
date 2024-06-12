#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;
using namespace sf;

//Permet de faire une rotation sur un point x, y ou z, z est la profondeur
void pivot(vector<Vector3f>& vecteur, float angle, const Vector3f& axe) 
{
    Vector3f centre{175, 200, 100};
    float rad = angle * M_PI / 180; // Conversion de degrés en radians
     
    for (int i = 0; i < vecteur.size(); i++)
    {
        // Translation pour placer le centre de rotation à l'origine
        vecteur[i].x -= centre.x;
        vecteur[i].y -= centre.y;
        vecteur[i].z -= centre.z;

        // Rotation autour de l'axe Y
        if(axe.y == 1)
        {
            float x = vecteur[i].x * cos(rad) - vecteur[i].z * sin(rad);
            float z = vecteur[i].x * sin(rad) + vecteur[i].z * cos(rad);
            vecteur[i].x = x;
            vecteur[i].z = z;
        }
        // Rotation autour de l'axe X
        if(axe.x == 1)
        {
            float y = vecteur[i].y * cos(rad) - vecteur[i].z * sin(rad);
            float z = vecteur[i].y * sin(rad) + vecteur[i].z * cos(rad);
            vecteur[i].y = y;
            vecteur[i].z = z;
        }
        // Rotation autour de l'axe Z
        if(axe.z == 1)
        {
            float x = vecteur[i].x * cos(rad) - vecteur[i].y * sin(rad);
            float y = vecteur[i].x * sin(rad) + vecteur[i].y * cos(rad);
            vecteur[i].x = x;
            vecteur[i].y = y;
        }

        // Retranslation pour remettre le centre de rotation à sa position initiale
        vecteur[i].x += centre.x;
        vecteur[i].y += centre.y;
        vecteur[i].z += centre.z;
    }
}

// Dessiner les vecteurs du cub
void dessinerVecteur(vector<Vector2f>&matrixCube,RenderWindow& window)
{
    for (int i = 0; i < matrixCube.size() - 1; i++) 
        {
            sf::Vertex line[] = 
            {
                sf::Vertex(matrixCube[i], sf::Color::Red),
                sf::Vertex(matrixCube[i + 1], sf::Color::Red)
            };

            window.draw(line, 2, sf::Lines);
        }
}

//ProjectionOrthographique transformer la 3D vers de la 2D
vector<Vector2f> projectionOrthographique(const vector<Vector3f>& points3D, RenderWindow& window) 
{
    vector<Vector2f> points2D(points3D.size());
    for (int i = 0; i < points3D.size(); i++) 
    {
        float x = points3D[i].x +window.getSize().x / 2;
        float y = -points3D[i].y + window.getSize().y / 2;
        points2D[i] = Vector2f(x, y);
    }
    return points2D;
}


void loopWindow(RenderWindow& window,vector<Vector3f>& matrixCube)
{
     Event event;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        
        Vector3f pivotPointAxe = {1, 1, 1};
        pivot(matrixCube,1,pivotPointAxe);
        vector<Vector2f> projectionCube = projectionOrthographique(matrixCube,window);
        dessinerVecteur(projectionCube,window);   

        window.display();
    }
}

int main()
{

   vector<Vector3f> matrixCube
    {
        {100, 100, 0}, // Point A
        {300, 100, 0}, // Point B
        {300, 300, 0}, // Point C
        {100, 300, 0}, // Point D
        {100, 100, 0}, // Retour au Point A pour fermer le carré

        {100, 100, 200}, // Point E, superposé au Point A
        {300, 100, 200}, // Point F, superposé au Point B
        {300, 300, 200}, // Point G, superposé au Point C
        {100, 300, 200}, // Point H, superposé au Point D
        {100, 100, 200}, // Retour au Point E pour fermer le carré supérieur

        // Connexion des points entre les deux carrés
        
        {100, 100, 0}, // Point A
        {300, 100, 0}, // Point B
        {300, 100, 200}, // Point F
        {300, 300, 200}, // Point G
        {300, 300, 0}, // Point C
        {100, 300, 0}, // Point D   
        {100, 300, 200}, // Point H, superposé au Point D 
};
  
    RenderWindow window(VideoMode(1300,800),"Matrix");  
    window.setFramerateLimit(60);
    loopWindow(window,matrixCube);
}