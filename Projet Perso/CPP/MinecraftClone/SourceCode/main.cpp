/*
	Projet Minecraft Clone
	Auteur : Mehdi Mazouz
	Date : 2024

	Ce projet a pour but de créer un moteur de jeu en C++ ainsi qu'un jeu.

	L'objectif de ce projet est de développer un moteur de jeu qui soit le plus optimisé et extensible possible.
	Je ne m'aiderai pas de ChatGPT et n'utiliserai que des ressources en ligne et sur papier.

	Le projet sera en anglais pour m'exercer.

	* Prédiction *
	Amusement : 10/10 Vraiment
	Difficulté : 10/10 C'est long et difficile
	Utilité : 10/10 énormément appris
*/

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// Initialize GLFW
	glfwInit();



	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Minecraft Clone"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Minecraft Clone", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);


	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
