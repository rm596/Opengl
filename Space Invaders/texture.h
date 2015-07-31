#ifndef texture

extern unsigned int texture[1]; // Array of texture ids.

void loadExternalTextures()			
{
	// Local storage for bmp image data.
	BitMapFile *image[1];

	// Load the image.
	image[0] = getbmp("stars.bmp"); 

	// Create texture object texture[0]. 
	glBindTexture(GL_TEXTURE_2D, texture[0]); 

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}



#endif // !texture
