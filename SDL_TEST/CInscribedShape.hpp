
#ifndef CInscribedShape_hpp
#define CInscribedShape_hpp

#include "CircleDraw.hpp"

class CInscribedShape : public CircleDraw
{
public:
    CInscribedShape(SDL_Renderer* renderer, int r, LDPoint c, int numVerts);
    ~CInscribedShape();
    
    std::vector<LDPoint> nonSequentialPerimeterPoints;
    
    const std::vector<int>& getVertexIndecies();
    const std::vector<LDPoint>& getVertexPoints();
    
    void init();
    
    void move(LDPoint amount) override;
    void recenter() override;
    void draw() override;
    virtual void rotate(int amount);
    
    bool isInsidePerimeter(LDPoint testPoint) override;
    bool isInsidePerimeter(CInscribedShape& other);
    
    void handleKeyStates(const Uint8*& keystates);
    
    
protected:
    int numVertices;
    std::vector<LDPoint> vertexPoints;
    std::vector<int> vertexIndecies;
    
    void sortPerimeterPoints();
    void updateVertexPoints();
    void assignVertexIndexes();
    
};








#endif
