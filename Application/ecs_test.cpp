#include <iostream>

#include "ECS/ECS.hpp"

#include <cmath>

typedef eng::ECS<64> ECS;

struct Position {
    float x, y;
};

struct Velocity {
    float vx, vy;
};

struct Mass {
    float m;
};

struct Forces {
    float fx, fy;
};

void momentum(Velocity* v, Mass* m) {
    std::cout << "momentum : " << sqrtf(v->vx*v->vx + v->vy*v->vy)*m->m << std::endl;
}

void print_position(Position* p) {
    std::cout << "position : " << p->x << ", " << p->y << std::endl;
}

void gravity(Forces* f) {
    f->fy += -9.81;
}

void force_init(Forces* f) {
    f->fx = 0;
    f->fy = 0;
}

float get_time() {
    return 0.5f;
}

void newton(Position* p, Velocity* v, Forces* f) {
    float t = get_time();

    v->vx += f->fx*t;
    v->vy += f->fy*t;

    p->x += v->vx*t;
    p->y += v->vy*t;
}

void print_mask(ECS& ecs) {
    auto l = ecs.list_mask();

    for (auto i : l) {
        std::cout << "Bitmask : " << ecs.to_string(i.first) << ", nbr element : " << i.second << std::endl; 
    }
}

int main() {
    std::cout << "Begin program" << std::endl;

    ECS ecs;

    ecs.register_component<Position>();
    ecs.register_component<Velocity>();
    ecs.register_component<Mass>();
    ecs.register_component<Forces>();

    ECS::EntityID ent1 = ecs.create_entity();
    ecs.give_component(ent1, Position{1,2});
    ecs.give_component(ent1, Velocity{0,0});
    ecs.give_component(ent1, Mass{3});

    ECS::EntityID ent2 = ecs.create_entity();
    ecs.give_component(ent2, Position{0,0});
    ecs.give_component(ent2, Velocity{1,0});
    ecs.give_component(ent2, Mass{5});
    ecs.give_component(ent2, Forces{0,0});

    ECS::EntityID ent3 = ecs.create_entity();
    ecs.give_component(ent3, Position{5,5});

    auto l1 = ecs.list_mask();
    for (auto i : l1) {
        std::cout << "Bitmask : " << ecs.to_string(i.first) << ", # element = " << i.second << std::endl;
    }

    ecs.erase_empty_arena(true);

    l1 = ecs.list_mask();
    for (auto i : l1) {
        std::cout << "Bitmask : " << ecs.to_string(i.first) << ", # element = " << i.second << std::endl;
    }

    std::cout << "End program" << std::endl;

    return 0;
}