#ifndef FLOW_HPP
#define FLOW_HPP

enum Commands : char
{
  START_STREAMING = '#',
  STOP_STREAMING = '!'
};

#pragma pack(push,1)
struct Flow
{
  short deltaX;
  short deltaY;
  float range;
  short mili_sec;
};

#pragma pack(pop)

#endif
