#include <iostream>

#include "../../Bolt/src/Bolt.hpp"

class Foo : public Bolt::Application {
public:
	Foo() {}

	~Foo() {}
};

Bolt::Application* Bolt::createApplication() { return new Foo(); }
