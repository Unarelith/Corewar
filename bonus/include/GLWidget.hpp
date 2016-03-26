/*
 * =====================================================================================
 *
 *       Filename:  GLWidget.hpp
 *
 *    Description:  
 *
 *        Created:  23/02/2016 18:59:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GLWIDGET_HPP_
#define GLWIDGET_HPP_

#include <memory>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include <QTimer>

#include "AppClock.hpp"
#include "Camera.hpp"

class CorewarRenderer;

#include <QAudioBuffer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
	
	public:
		GLWidget(QWidget *parent = nullptr)
			: QOpenGLWidget(parent) {}
		
	public slots:
		void process();
		void processAudioBuffer(const QAudioBuffer &buffer);
		
	protected:
		virtual void initializeGL();
		virtual void resizeGL(int width, int height);
		virtual void paintGL();
		
	private:
		bool prepareShaderProgram(const QString &vertexShaderPath, const QString &fragmentShaderPath);
		
		QMatrix4x4 m_projMatrix;
		
		QOpenGLVertexArrayObject m_vao;
		QOpenGLShaderProgram m_shader;
		
		Camera m_camera;
		std::shared_ptr<CorewarRenderer> m_renderer{nullptr};
		
		AppClock m_clock;
		QTimer m_timer;
};

#endif // GLWIDGET_HPP_
