#pragma once

#include <string>
#include <glad/glad.h>

namespace Renderer
{
	class Texture2D 
	{
	public:
		Texture2D(
			const GLuint width, 
			const GLuint height, 
			const unsigned char* data, 
			const unsigned int channels, 
			const GLenum filter, 
			const GLenum wrapMode
		);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D(const Texture2D&&);
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&&);
		~Texture2D();

		void bind() const;
	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;
	};
}