//-------------------------------------------------------------------
//^CgζΚ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Tutorial.h"
#include  "Task_Title.h"

namespace  Tutorial
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		this->imageName = "TutorialImg";
		DG::Image_Create(this->imageName, "./data/image/tutorialTest.png");//ΌΜC[W

	
		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
		DG::Image_Erase(this->imageName);
		return true;
	}
	//-------------------------------------------------------------------
	//uϊ»v^XNΆ¬ΙPρΎ―s€
	bool  Object::Initialize()
	{
		//X[p[NXϊ»
		__super::Initialize(defGroupName, defName, true);
		//\[XNXΆ¬or\[X€L
		this->res = Resource::Create();

		//f[^ϊ»
		this->posy = 0;

			
		DG::EffectState().param.bgColor = ML::Color(1, 0, 0, 0);
		//^XNΜΆ¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uIΉv^XNΑΕΙPρΎ―s€
	bool  Object::Finalize()
	{
		//f[^^XNπϊ


		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//ψ«p¬^XNΜΆ¬
			auto nextTask = Title::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[Ιs€
	void  Object::UpDate()
	{
		auto in = DI::GPad_GetState("P1");

		if (in.LStick.D.on || in.HD.on)
		{
			this->posy -= 2;
		}
		if (in.LStick.U.on || in.HU.on)
		{
			this->posy += 2;
		}

		//posyΜΝΝέθ
		if (this->posy < -528)
		{
			this->posy = -528;
		}
		if (this->posy > 0)
		{
			this->posy = 0;
		}

		if (in.ST.down)
		{
			if (in.ST.down)
			{
				//©gΙΑΕvΏ
				this->Kill();
			}
		}
	}
	//-------------------------------------------------------------------
	//uQc`ζvPt[Ιs€
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(0, 0, 1280, 1248);
		ML::Box2D src(0, 0,1280, 1248);

		draw.Offset(0, this->posy);
		DG::Image_Draw(this->res->imageName, draw, src);
	}

	void  Object::Render3D_L0()
	{
		
	}
	//
	//ΘΊΝξ{IΙΟXsvΘ\bh
	//
	//-------------------------------------------------------------------
	//^XNΆ¬ϋ
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//Q[GWΙo^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//CjVCYΙΈs΅½ηKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//\[XNXΜΆ¬
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}