/*
 * Author: Victor Sand (victor.sand@gmail.com)
 *
 */

#ifndef FORGE_H_
#define FORGE_H_

#include <string>
#include <vector>
#include <list>
#include <fstream>

namespace osp {
  
class BricksHeader;
template <class T>
class Brick;

class Forge {
public:
  static Forge * New();
  ~Forge();

  // Setters for various variables
  void SetInFilename(std::string _inFilename);
  void SetOutFilename(std::string _outFilename);
  void SetBrickDimensions(unsigned int _xBrickDim,
                          unsigned int _yBrickDim,
                          unsigned int _zBrickDim);
  void SetSpatialScaling(float _spatialScaling);
  void SetTemporalScaling(float _temporalScaling);

  // Execute all construction steps
  bool Construct();

private:
  Forge();
  Forge(const Forge&);

  std::string inFilename_;
  std::string outFilename_;
  std::string tempFilename_;

  const unsigned int paddingWidth_ = 1;

  std::vector<Brick<float>*> bricks_;

  // Error scaling exponents
  float spatialScaling_;
  float temporalScaling_;

  // Data that ends up in the out file
  unsigned int gridType_;
  unsigned int numTimesteps_;
  unsigned int xDim_;
  unsigned int yDim_;
  unsigned int zDim_;
  unsigned int xBrickDim_;
  unsigned int yBrickDim_;
  unsigned int zBrickDim_;
  unsigned int xNumBricks_;
  unsigned int yNumBricks_;
  unsigned int zNumBricks_;
  unsigned int dataSize_;

  // Additional metadata
  unsigned int numBricksBaseLevel_;
  unsigned int numLevels_;
  unsigned int numBricksPerOctree_;
  unsigned int numBricksTotal_;
  unsigned int xPaddedDim_;
  unsigned int yPaddedDim_;
  unsigned int zPaddedDim_;
  unsigned int xPaddedBrickDim_;
  unsigned int yPaddedBrickDim_;
  unsigned int zPaddedBrickDim_;

  // Read metadata
  bool ReadMetadata();
  // Create an octree for every timestep, save in one common file
  bool CreateOctree();
  // Delete the created temp file
  bool DeleteTempFile();
  // Use temp octrees to create TSP tree
  //bool ConstructTSPTree();
  // Use temp octrees to create TSP tree (spatial ordering)
  bool ConstructTSPTreeSpatial();

  std::fstream instream_;

  // Points to first data entry after header
  std::ios::pos_type headerOffset_;

  // Calculate Z-order index from x, y, z coordinates
  uint32_t ZOrder(uint16_t x, uint16_t y, uint16_t z);

};


}

#endif

