#ifndef FLOW_HPP
#define FLOW_HPP

#pragma pack(push,1)
class Flow {
  public:
  int deltaX;
  int deltaY;
  float range;
  Flow(int x,int y, int r): deltaX(x),deltaY(y),range(r){};
};

#pragma pack(pop)

#endif
