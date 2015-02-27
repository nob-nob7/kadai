//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"

enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

struct Ball{
	float x;
	float y;
	float x_speed;
	float y_speed;
	float width;
	float height;

}ball;



//動き
void Ball_Move(){

	ball.x += ball.x_speed;
	ball.y += ball.y_speed;
	ball.width = 20;
	ball.height = 20;



	if (Window::WIDTH / 2 <= ball.x + ball.width){
		ball.x_speed *= -1;
	}

	if (-Window::WIDTH / 2 >= ball.x - ball.width){
		ball.x_speed *= -1;
	}

	if (Window::HEIGHT / 2 <= ball.y + ball.height)  {
		ball.y_speed *= -1;
	}

	if (-Window::HEIGHT / 2 >= ball.y - ball.height){
		ball.y_speed *= -1;
	}

}

void gravity(AppEnv& env){

	if (env.isPressKey('G')){
		ball.y_speed += -5;
	}

	if (ball.y - ball.height  < -HEIGHT / 2){
		ball.y = -HEIGHT / 2 + ball.height;
	}

}

//初期化
void Init(){
	ball.x = -100;
	ball.y = 150;
	ball.x_speed = 2;
	ball.y_speed = 2;
}

int main()
{
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

	Init();
	while (env.isOpen()){

		if (env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

		Ball_Move();

		gravity(env);

		env.setupDraw(); // 描画準備

		drawFillCircle(ball.x, ball.y, ball.width, ball.height, 100, Color(0, 1, 1));


		env.update();
	}
}