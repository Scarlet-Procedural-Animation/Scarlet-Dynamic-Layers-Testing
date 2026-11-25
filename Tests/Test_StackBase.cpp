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

TEST_CASE("Stack Base - Can add layers (size check)")
{
    StackT stack;
    CHECK(stack.size() == 0);

    stack.addLayer(LayerT(0, 0));
    CHECK(stack.size() == 1);

    stack.addLayer(LayerT(0, 0));
    CHECK(stack.size() == 2);
}

TEST_CASE("Stack Base - Can access layers")
{
    StackT stack;
    for (int i = 0; i < 3; i++)
        stack.addLayer(LayerT(i, i));

    for (int i = 0; i < 3; i++)
        REQUIRE_NOTHROW(stack[i]);

    for (int i = 0; i < 3; i++)
    {
        CHECK(stack[i].getType() == i);
        CHECK(stack[i].getPriority() == i);
    }
}
