# include <Siv3D.hpp> // Siv3D v0.6.14
#include "Main.h"

struct Bullet {
	Vec2 position;  // 玉の位置
	Vec2 velocity;  // 玉の速度
	double radius;  // 玉の半径
	Color color;    // 玉の色
	bool active;    // 玉がアクティブかどうか

	// 玉の更新メソッド
	void update() {
		if (active) {
			position += velocity; // 位置を速度に基づいて更新

			// 画面外に出たら無効にする
			if (position.x < 0 || position.x > Scene::Width() || position.y < 0 || position.y > Scene::Height()) {
				active = false;
			}
		}
	}

	// 玉の描画メソッド
	void draw() const {
		if (active) {
			Circle(position, radius).draw(color); // 玉を描画
		}
	}
};

void Main() {
	// プレイヤーの位置
	Vec2 playerPos(Scene::Width() / 2, Scene::Height() - 50);

	// 玉の最大数
	const int maxBullets = 100;

	// 玉の配列を作成
	Array<Bullet> bullets(maxBullets);

	// 一度に発射する玉の方向の配列（5つの角度で発射するためのオフセット）
	const Array<double> shotAngles = { -20_deg, -10_deg, 0_deg, 10_deg, 20_deg };

	while (System::Update()) {
		// プレイヤーの移動
		if (KeyLeft.pressed()) {
			playerPos.x -= 5;
		}
		if (KeyRight.pressed()) {
			playerPos.x += 5;
		}

		// スペースキーが押されたら配列の角度に応じて玉を発射
		if (KeySpace.down()) {
			for (double angleOffset : shotAngles) {
				for (auto& bullet : bullets) {
					if (!bullet.active) {
						bullet.position = playerPos;                            // 玉の初期位置はプレイヤーの位置
						bullet.velocity = Vec2(0, -10).rotated(angleOffset);    // 発射角度を配列の角度で調整
						bullet.radius = 5;                                      // 玉の半径
						bullet.color = Palette::Orange;                         // 玉の色
						bullet.active = true;                                   // 玉をアクティブにする
						break; // 1つの玉をアクティブにしたらループを抜ける
					}
				}
			}
		}

		// 各玉を更新・描画
		for (auto& bullet : bullets) {
			bullet.update(); // 玉の位置を更新
			bullet.draw();   // 玉を描画
		}

		// プレイヤーを描画
		Rect(playerPos.x - 20, playerPos.y, 40, 20).draw(Palette::Skyblue); // プレイヤーは四角形
	}
}



	
