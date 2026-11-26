#include "StackBase.h"
#include "LayerMono.h"

#include "doctest.h"

using namespace DynamicLayers;

// Test Wrapper for Stack Base (to allow instantiation)
template<typename TOutValue, template <class, class, class> class TLayer>
class StackBaseTest final : public sb::StackBase<TOutValue, char, TLayer, StackBaseTest<TOutValue, TLayer>>
{
public:
    StackBaseTest() {}
    virtual ~StackBaseTest() override {}
};

using StackT = StackBaseTest<int, LayerMono>;
using LayerT = LayerMono<int, char, StackT>;


TEST_CASE("Stack Base - Empty by default")
{
    StackT stack;
    CHECK(stack.size() == 0);
}

TEST_CASE("Stack Base - Can add & access layers")
{
    StackT stack;
    int num_layers = 3;
    for (int i = 0; i < num_layers; i++)
        stack.addLayer(LayerT(i, i));

    CHECK(stack.size() == num_layers);

    for (int i = 0; i < num_layers; i++)
        REQUIRE_NOTHROW(stack[i]);

    for (int i = 0; i < num_layers; i++)
    {
        CHECK(stack[i].getType() == i);
        CHECK(stack[i].getPriority() == i);
    }
}

TEST_CASE("Stack Base - Can remove layers")
{
    StackT stack;
    int num_layers = 3;
    std::vector<INT> layer_ids;
    for (int i = 0; i < num_layers; i++)
        layer_ids.push_back(stack.addLayer(LayerT(i, i)));

    CHECK(stack.size() == num_layers);

    for (int i = 0; i < num_layers; i++)
    {
        stack.removeLayer(layer_ids[i]);
        CHECK(stack.size() == num_layers - (i + 1));
    }
}


TEST_CASE("Stack Base - Can access order")
{
    StackT stack;
    CHECK_NOTHROW(stack.getOrder());
}

TEST_CASE("Stack Base - Same priority layers are ordered in the introduction order")
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> layer_ids;
    int num_layers = 3;
    for (int i = 0; i < num_layers; i++)
        layer_ids.push_back(stack.addLayer(LayerT(0, 0)));

    for (int i = 0; i < num_layers; i++)
    {
        CHECK(stack.getOrder()[i] == layer_ids[i]);
    }
}

TEST_CASE("Stack Base - Unique priority layers are ordered correctly")
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {3, 1, 2, 0};
    std::vector<INT> correct_order = {3, 1, 2, 0};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(0, priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order[i]);
    }
}

TEST_CASE("Stack Base - Duplicate priority layers are ordered correctly")
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {3, 1, 3, 0, 2, 1};
    std::vector<INT> correct_order = {3, 1, 5, 4, 0, 2};

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(0, priorities[i]));

    for (int i = 0; i < priorities.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order[i]);
    }
}

TEST_CASE("Stack Base - Stack order handles layer removal correctly")
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    std::vector<INT> priorities = {3, 1, 3, 0, 2, 1};
    std::vector<INT> correct_order = {3, 1, 4, 0, 2}; // Layer 5 is removed

    for (int i = 0; i < priorities.size(); i++)
        stack.addLayer(LayerT(0, priorities[i]));

    stack.removeLayer(5);

    for (int i = 0; i < correct_order.size(); i++)
    {
        CHECK(stack.getOrder()[i] == correct_order[i]);
    }
}


TEST_CASE("Stack Base - Indices are freed and reused after removal")
{
    StackT stack;
    REQUIRE_NOTHROW(stack.getOrder());

    int num_layers = 3;
    for (int i = 0; i < num_layers; i++)
        stack.addLayer(LayerT(0, 0));

    stack.removeLayer(1); // Remove middle layer

    // Newly added layer shall have id = 1
    CHECK(stack.addLayer(LayerT(0, 0)) == 1);
    CHECK(stack.size() == num_layers); // Stack has same size as before
}
