# include <Siv3D.hpp> // Siv3D v0.6.14
#include "Main.h"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };


	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	while (System::Update())
	{
		// スライダー | Slider
		SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
	}
}
