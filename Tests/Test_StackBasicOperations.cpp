#include "StackBasicOperations.h"
#include "LayerMono.h"

#include "doctest.h"

using namespace DynamicLayers;

TEST_CASE("Stack Basic Operations - Mono Layer can be created")
{
    REQUIRE_NOTHROW(StackBasicOperations<int, LayerMono> stack);
}

TEST_CASE("Stack Basic Operations - Empty by default")
{
    using StackT = StackBasicOperations<int, LayerMono>;
    using LayerT = LayerMono<int, BlendBasicOperations, StackT>;
    StackT stack;

    CHECK(stack.size() == 0);
}

TEST_CASE("Stack Basic Operations - Can add layers")
{
    using StackT = StackBasicOperations<int, LayerMono>;
    using LayerT = LayerMono<int, BlendBasicOperations, StackT>;
    StackT stack;
    stack.addLayer(LayerT(BlendBasicOperations::Override, 0));
    stack.addLayer(LayerT(BlendBasicOperations::Add, 1));
    stack.addLayer(LayerT(BlendBasicOperations::Multiply, 2));

    CHECK(stack.size() == 3);

    CHECK(stack[0].getType() == BlendBasicOperations::Override);
    CHECK(stack[0].getPriority() == 0);

    CHECK(stack[1].getType() == BlendBasicOperations::Add);
    CHECK(stack[1].getPriority() == 1);

    CHECK(stack[2].getType() == BlendBasicOperations::Multiply);
    CHECK(stack[2].getPriority() == 2);
}
