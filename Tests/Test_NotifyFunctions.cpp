#include "StackBasicOperations.h"
#include "LayerMono.h"

#include "doctest.h"

using namespace DynamicLayers;

using BasicOperations = StackBasicOperations<int, LayerMono>;
using LayerT = LayerMono<int, BlendBasicOperations, BasicOperations>;

TEST_CASE_TEMPLATE("Priority Changed Notify test - new priority, sink", StackT, BasicOperations)
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {0, 2, 2, 3, 4, 5};

    std::vector<INT> correct_order_pre = {0, 1, 2, 3, 4, 5};
    // Layer with id=5 changes it's priority to 1
    std::vector<INT> correct_order_post = {0, 5, 1, 2, 3, 4};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(static_cast<StackT::LayerBlendType>(0), priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_pre[i]);
    }

    // Changing layer priority
    stack[5].setPriority(1);

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_post[i]);
    }
}

TEST_CASE_TEMPLATE("Priority Changed Notify test - new priority, raise", StackT, BasicOperations)
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {0, 2, 2, 3, 4, 5};

    std::vector<INT> correct_order_pre = {0, 1, 2, 3, 4, 5};
    // Layer with id=1 changes it's priority to 6
    std::vector<INT> correct_order_post = {0, 2, 3, 4, 5, 1};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(static_cast<StackT::LayerBlendType>(0), priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_pre[i]);
    }

    // Changing layer priority
    stack[1].setPriority(6);

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_post[i]);
    }
}

TEST_CASE_TEMPLATE("Priority Changed Notify test - existing priority, sink", StackT, BasicOperations)
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {0, 2, 2, 3, 4, 5};

    std::vector<INT> correct_order_pre = {0, 1, 2, 3, 4, 5};
    // Layer with id=5 changes it's priority to 2
    std::vector<INT> correct_order_post = {0, 1, 2, 5, 3, 4};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(static_cast<StackT::LayerBlendType>(0), priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_pre[i]);
    }

    // Changing layer priority
    stack[5].setPriority(2);

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_post[i]);
    }
}

TEST_CASE_TEMPLATE("Priority Changed Notify test - existing priority, raise", StackT, BasicOperations)
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {0, 2, 3, 4, 5, 5};

    std::vector<INT> correct_order_pre = {0, 1, 2, 3, 4, 5};
    // Layer with id=0 changes it's priority to 5
    std::vector<INT> correct_order_post = {1, 2, 3, 0, 4, 5};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(static_cast<StackT::LayerBlendType>(0), priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_pre[i]);
    }

    // Changing layer priority
    stack[0].setPriority(5);

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order_post[i]);
    }
}
