#include "GameObject.h"
void GameObject::add_state_animation_pair(std::string state_name,std::string animation_name){
	state_animation_map[state_name]=animation_name;
}
void GameObject::defaultUpdate(){
	velocity=Vector2D(0,0);
	setState("standing");
	Mix_HaltChannel(-1);
}
void GameObject::update(bool coll_cond){
	for(std::vector<int>::size_type i = 0; i != events.size(); i++) {
		events[i]->handleEvent(coll_cond);
	}
	/*if(width==50){
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)){
		setState("walk_right");
		velocity.setX(1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
		setState("walk_left");
		velocity.setX(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		setState("walk_right");
		velocity.setY(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		setState("walk_left");
		velocity.setY(1);
	}
	if(position.getY()>400){
		position.setY(400);
	}
}
else{
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
		setState("walk_right");
		velocity.setX(1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)){
		setState("walk_left");
		velocity.setX(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		setState("walk_right");
		velocity.setY(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		setState("walk_left");
		velocity.setY(1);
	}
	if(position.getY()>400){
		position.setY(400);
	}
}
*/
	//acceleration.setY(6);
	if(coll_cond==false){
	velocity+=acceleration;
	position+=velocity;
	collision_polygon->updatePosition(position.getX(),position.getY());
	}
}
void GameObject::draw(){
	SDL_Rect destinationRectangle;
	SDL_Rect sourceRectangle;
	Animation* animation=model->getAnimation(getAnimationName(state));
	int refresh_rate=100/(animation->speed);
	int frame_number=int((SDL_GetTicks()/refresh_rate) %(animation->frame_ids.size()));
	sourceRectangle.x = (animation->frame_ids[frame_number].second-1)*model->width_of_frame;
	sourceRectangle.y = (animation->frame_ids[frame_number].first-1)*model->height_of_frame;
	destinationRectangle.x = position.getX();
	destinationRectangle.y = position.getY();
	destinationRectangle.w =width;
	destinationRectangle.h =height;
	sourceRectangle.w=model->width_of_frame;
	sourceRectangle.h=model->height_of_frame;
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),model->texture,&sourceRectangle,&destinationRectangle,0,0,SDL_FLIP_NONE);
}
GameObject::GameObject(std::string state,Model* model,float width,float height,Vector2D position):collision_polygon(new CollisionPolygon(position.getX(),position.getY(),width,height)){
		static int object_num=0;
		GameObject::state=state;
		GameObject::position = position;
		GameObject::model=model;
		GameObject::velocity = Vector2D(0,0);
		GameObject::acceleration = Vector2D(0,0);
		GameObject::width=width;
		GameObject::height=height;
		GameObject::object_id="object"+std::to_string(static_cast<long long>(object_num));
		object_num++;
		updated=false;
	}
GameObject::GameObject(std::string state,Model* model,float width,float height,Vector2D position,std::string object_id):collision_polygon(new CollisionPolygon(position.getX(),position.getY(),width,height)){
	static int object_num=0;
		GameObject::state=state;
		GameObject::position = position;
		GameObject::model=model;
		GameObject::velocity = Vector2D(0,0);
		GameObject::acceleration = Vector2D(0,0);
		GameObject::width=width;
		GameObject::height=height;
		GameObject::object_id="object"+std::to_string(static_cast<long long>(object_num));
		object_num++;
		updated=false;
	GameObject::object_id=object_id;
}
void GameObject::addEvent(Event* event){
	events.push_back(event);
	event->parent=this;
}