class GameObjects
{
	public:
		int type_index;
		int score;
		double xCurrPos;
		double yCurrPos;
		double xPrevPos;
		double yPrevPos;
		double xSpeed;	
		double ySpeed; 

		// GameObjects(double xc,double yc,double xp,double yp,double xs,double ys)
		// {
		// 	score= 0;
		// 	xCurrPos=xc;
		// 	yCurrPos=yc;
		// 	xPrevPos=xp;
		// 	yPrevPos=yp;
		// 	xSpeed=xs;
		// 	ySpeed=ys;
		// }
		virtual void checkLimit(){};
};

class Bot : public GameObjects
{
	public:

		
		Bot(double xc,double yc,double xp,double yp,double xs,double ys)
		{
			type_index=0;
			score= 0;
			xCurrPos=xc;
			yCurrPos=yc;
			xPrevPos=xp;
			yPrevPos=yp;
			xSpeed=xs;
			ySpeed=ys;
		};
		void checkLimit() override
		{
			
		}
};

class Puck : public GameObjects
{
	public:

		Puck(double xc,double yc,double xp,double yp,double xs,double ys)
		{
			type_index=1;
			xCurrPos=xc;
			yCurrPos=yc;
			xPrevPos=xp;
			yPrevPos=yp;
			xSpeed=xs;
			ySpeed=ys;
		};
		void checkLimit() override
		{
			
		}
};

class Player : public GameObjects
{
	public:

		Player(double xc,double yc,double xp,double yp,double xs,double ys)
		{
			type_index=2;
			score= 0;
			xCurrPos=xc;
			yCurrPos=yc;
			xPrevPos=xp;
			yPrevPos=yp;
			xSpeed=xs;
			ySpeed=ys;
		};
		void checkLimit() override
		{
			
		}
};
