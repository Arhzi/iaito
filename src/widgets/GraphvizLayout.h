#ifndef GRAPHVIZLAYOUT_H
#define GRAPHVIZLAYOUT_H

#include "GraphLayout.h"
#include "core/Iaito.h"

class GraphvizLayout : public GraphLayout
{
public:
    enum class LayoutType {
        DotOrtho,
        DotPolyline,
        Sfdp,
        Neato,
        TwoPi,
        Circo,
    };
    enum class Direction { TB, LR };
    GraphvizLayout(LayoutType layoutType, Direction direction = Direction::TB);
    virtual void CalculateLayout(
        std::unordered_map<ut64, GraphBlock> &blocks,
        ut64 entry,
        int &width,
        int &height) const override;

private:
    Direction direction;
    LayoutType layoutType;
};

#endif // GRAPHVIZLAYOUT_H
