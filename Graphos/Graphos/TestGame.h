//
//  TestGame.h
//  Graphos
//
//  Created by Colden Cullen on 5/1/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

#ifndef __TEST_GAME
#define __TEST_GAME

#include "GraphosGame.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Helpers.h"
#include "Config.h"
#include "Flipper.h"

namespace Graphos
{
	class TestGame : public GraphosGame
	{
	private:
		float maxPlungerHeight;
		float flipperRotation;
		float rotationValue;
		float initialPlungerHeight;
		bool isReset;
		Vector3 ballSpawn;
		Flipper* leftFlipper;
		Flipper* rightFlipper;
		GameObject* plunger;
		GameObject* ball;

		bool Initialize( void )
		{
			leftFlipper = nullptr;
			rightFlipper = nullptr;
			plunger = nullptr;

			flipperRotation = 45.0f;
			rotationValue = 360.0f;
			maxPlungerHeight = -2.5f;
			isReset = true;

			return true;
		}

		bool Update( float deltaTime )
		{
#ifdef _WIN32
			// Quit condition
			if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			{
				if( currentState == Game )
					currentState = Menu;
				else if( currentState == Menu )
					return false;
			}

			// Reset
			if( Input::Get().IsKeyDown( VK_F5, true ) )
				Reset();

			if( currentState == Game )
			{
				if( leftFlipper == nullptr )
				{
					leftFlipper = static_cast<Flipper*>( GameObject::GetGameObject( "LeftFlipper" ) );
					leftFlipper->transform.Rotate( 0.0f, 0.0f, flipperRotation );

					rightFlipper = static_cast<Flipper*>( GameObject::GetGameObject( "RightFlipper" ) );
					rightFlipper->transform.Rotate( 0.0f, 0.0f, -flipperRotation );

					plunger = GameObject::GetGameObject( "Plunger" );
					initialPlungerHeight = plunger->transform.Position().y;

					ball = GameObject::GetGameObject( "Ball" );
					ballSpawn = ball->transform.Position();
				}
	
				#pragma region Camera
				/*
				// Move camera
				if( Input::Get().IsKeyDown( VK_LEFT, false ) )
				{
					camera->Owner()->transform.Rotate( 0.0f, -3.0f * deltaTime, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
				{
					camera->Owner()->transform.Rotate( 0.0f, 3.0f * deltaTime, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_UP, false ) )
				{
					camera->Owner()->transform.Rotate( 3.0f * deltaTime, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_DOWN, false ) )
				{
					camera->Owner()->transform.Rotate( -3.0f * deltaTime, 0.0f, 0.0f );
				}
	
				// Rotate camera
				if( Input::Get().IsKeyDown( VK_A, false ) )
				{
					camera->Owner()->transform.Translate( -1.0f * deltaTime, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_D, false ) )
				{
					camera->Owner()->transform.Translate( 1.0f * deltaTime, 0.0f, .0f );
				}
				if( Input::Get().IsKeyDown( VK_W, false ) )
				{
					camera->Owner()->transform.Translate( 0.0f, 0.0f, 1.0f * deltaTime );
				}
				if( Input::Get().IsKeyDown( VK_S, false ) )
				{
					camera->Owner()->transform.Translate( 0.0f, 0.0f, -1.0f * deltaTime );
				}
				*/
				#pragma endregion

				#pragma region Flipper Control
				// Flip left flip
				if( Input::Get().IsKeyDown( VK_LEFT, false ) )
				{
					if( leftFlipper->transform.Rotation().z > -flipperRotation )
					{
						leftFlipper->transform.Rotate( 0.0f, 0.0f, -rotationValue * deltaTime );
						//leftFlipper->GetIngredient<Collider>()->bounce = 1.2f;
					}
				}
				// Rotate back
				else
				{
					if( leftFlipper->transform.Rotation().z < flipperRotation )
					{
						leftFlipper->transform.Rotate( 0.0f, 0.0f, rotationValue * deltaTime );
					}
				}

				// Right flipper
				if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
				{
					if( rightFlipper->transform.Rotation().z < flipperRotation )
					{
						rightFlipper->transform.Rotate( 0.0f, 0.0f, rotationValue * deltaTime );
						//rightFlipper->GetIngredient<Collider>()->bounce = 1.2f;
					}
				}
				// Rotate back
				else
				{
					if( rightFlipper->transform.Rotation().z > -flipperRotation )
					{
						rightFlipper->transform.Rotate( 0.0f, 0.0f, -rotationValue * deltaTime );
					}
				}
				#pragma endregion

				#pragma region Plunger Control
				if( isReset && Input::Get().IsKeyDown( VK_LBUTTON ) && plunger->transform.Position().y > maxPlungerHeight )
				{
					plunger->transform.Translate( 0.0f, -0.3f * deltaTime, 0.0f );
				}
				else if ( plunger->transform.Position().y < initialPlungerHeight )
				{
					plunger->transform.Translate( 0.0f, 3.0f * deltaTime, 0.0f );
					if( isReset ) ball->GetIngredient<Rigidbody>()->AddForce( -0.1f, -plunger->transform.Position().y, 0.0f );
					isReset = false;
				}
				#pragma endregion

				#pragma region Ball Reset
				if( ball->transform.Position().y < -1.9f )
				{
					isReset = true;
				}

				if (isReset)
				{
					ball->transform.Translate(	ballSpawn.x - ball->transform.Position().x, 
												ballSpawn.y - ball->transform.Position().y, 
												ballSpawn.z - ball->transform.Position().z );
					ball->GetIngredient<Rigidbody>()->angularVelocity = Vector3( 0.0f, 0.0f, 0.0f );
					ball->GetIngredient<Rigidbody>()->linearVelocity = Vector3( 0.0f, 0.0f, 0.0f );
				}
				#pragma endregion
			}
#endif

			return true;
		}

		void Draw( void )
		{
			//ShaderController::Get().SetAllShadersUniform( "cameraMatrix", cam->transform.Matrix() );
			//ShaderController::Get().SetAllShadersUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

			ShaderController::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", /*cam->transform.WorldMatrix()*/Matrix::Identity );
			ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );
		}

		void Shutdown( void )
		{
			delete_s( camera );
		}
	};
}

#endif//__TEST_GAME