#ifndef _hexahedralgeom_h_
#define _hexahedralgeom_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Geometry/IGeometry3D.h"

/**
 * @brief The HexahedralGeom class represents a collection of hexahedra
 */
class SIMPLib_EXPORT HexahedralGeom : public IGeometry3D
{
  public:

    SIMPL_SHARED_POINTERS(HexahedralGeom)
    SIMPL_STATIC_NEW_MACRO(HexahedralGeom)
    SIMPL_TYPE_MACRO_SUPER_OVERRIDE(HexahedralGeom, Observable)

    ~HexahedralGeom() override;

    /**
     * @brief CreateGeometry
     * @param numHexas
     * @param vertices
     * @param name
     * @return
     */
    static Pointer CreateGeometry(size_t numHexas, const SharedVertexList::Pointer& vertices, const QString& name, bool allocate = true);

    /**
     * @brief CreateGeometry
     * @param hexas
     * @param vertices
     * @param name
     * @return
     */
    static Pointer CreateGeometry(const SharedHexList::Pointer& hexas, const SharedVertexList::Pointer& vertices, const QString& name);

    // -----------------------------------------------------------------------------
    // Inherited from SharedVertexOps
    // -----------------------------------------------------------------------------

    /**
     * @brief CreateSharedVertexList
     * @param numVertices
     * @return
     */
    static SharedVertexList::Pointer CreateSharedVertexList(size_t numVertices, bool allocate = true);

    // -----------------------------------------------------------------------------
    // Inherited from SharedEdgeOps
    // -----------------------------------------------------------------------------

    /**
     * @brief CreateSharedEdgeList
     * @param numEdges
     * @return
     */
    static SharedEdgeList::Pointer CreateSharedEdgeList(size_t numEdges, bool allocate = true);

    // -----------------------------------------------------------------------------
    // Inherited from SharedQuadOps
    // -----------------------------------------------------------------------------

    /**
     * @brief CreateSharedQuadLost
     * @param numQuads
     * @return
     */
    static SharedQuadList::Pointer CreateSharedQuadList(size_t numQuads, bool allocate = true);

    /**
     * @brief resizeQuadList
     * @param newNumQuads
     */
    void resizeQuadList(size_t newNumQuads);

    /**
     * @brief setQuads
     * @param quads
     */
    void setQuads(SharedQuadList::Pointer quads);

    /**
     * @brief getQuads
     * @return
     */
    SharedQuadList::Pointer getQuads() const;

    /**
     * @brief setVertsAtQuad
     * @param quadId
     * @param verts
     */
    void setVertsAtQuad(size_t quadId, size_t verts[4]);

    /**
     * @brief getVertsAtQuad
     * @param quadId
     * @param verts
     */
    void getVertsAtQuad(size_t quadId, size_t verts[4]) const;

    /**
     * @brief getVertCoordsAtQuad
     * @param quadId
     * @param vert1
     * @param vert2
     * @param vert3
     * @param vert4
     */
    void getVertCoordsAtQuad(size_t quadId, float vert1[3], float vert2[3], float vert3[3], float vert4[3]) const;

    /**
     * @brief getPointer
     * @param i
     * @return
     */
    size_t* getQuadPointer(size_t i) const;

    /**
     * @brief getNumberOfQuads
     * @return
     */
    size_t getNumberOfQuads() const;

    // -----------------------------------------------------------------------------
    // Inherited from SharedHexOps
    // -----------------------------------------------------------------------------

    /**
     * @brief CreateSharedHexList
     * @param numTets
     * @return
     */
    static SharedHexList::Pointer CreateSharedHexList(size_t numHexas, bool allocate = true);

    /**
     * @brief resizeHexList
     * @param newNumHexas
     */
    void resizeHexList(size_t newNumHexas);

    /**
     * @brief setHexahedra
     * @param tets
     */
    void setHexahedra(SharedHexList::Pointer hexas);

   /**
    * @brief getHexahedra
    * @return
    */
    SharedHexList::Pointer getHexahedra() const;

    /**
     * @brief setVertsAtHex
     * @param hexId
     * @param verts
     */
    void setVertsAtHex(size_t hexId, size_t verts[7]);

    /**
     * @brief getVertsAtHex
     * @param hexId
     * @param verts
     */
    void getVertsAtHex(size_t hexId, size_t verts[7]) const;

    /**
     * @brief getVertCoordsAtHex
     * @param hexId
     * @param vert1
     * @param vert2
     * @param vert3
     * @param vert4
     * @param vert5
     * @param vert6
     */
    void getVertCoordsAtHex(size_t hexId, float vert1[3], float vert2[3], float vert3[3], float vert4[3], float vert5[3], float vert6[3], float vert7[3], float vert8[3]) const;

    /**
     * @brief getHexPointer
     * @param i
     * @return
     */
    size_t* getHexPointer(size_t i) const;

    /**
     * @brief getNumberOfHexas
     * @return
     */
    size_t getNumberOfHexas() const;

    // -----------------------------------------------------------------------------
    // Inherited from IGeometry
    // -----------------------------------------------------------------------------

    /**
     * @brief initializeWithZeros
     */
    void initializeWithZeros() override;

    /**
     * @brief getNumberOfElements
     * @return
     */
    size_t getNumberOfElements() const override;

    /**
     * @brief findElementSizes
     * @return
     */
    int findElementSizes() override;

    /**
     * @brief getElementSizes
     * @return
     */
    FloatArrayType::Pointer getElementSizes() const override;

    /**
     * @brief deleteElementSizes
     */
    void deleteElementSizes() override;

    /**
     * @brief findElementsContainingVert
     * @return
     */
    int findElementsContainingVert() override;

    /**
     * @brief getElementsContainingVert
     * @return
     */
    ElementDynamicList::Pointer getElementsContainingVert() const override;

    /**
     * @brief deleteElementsContainingVert
     */
    void deleteElementsContainingVert() override;

    /**
     * @brief findElementNeighbors
     * @return
     */
    int findElementNeighbors() override;

    /**
     * @brief getElementNeighbors
     * @return
     */
    ElementDynamicList::Pointer getElementNeighbors() const override;

    /**
     * @brief deleteElementNeighbors
     */
    void deleteElementNeighbors() override;

    /**
     * @brief findElementCentroids
     * @return
     */
    int findElementCentroids() override;

    /**
     * @brief getElementCentroids
     * @return
     */
    FloatArrayType::Pointer getElementCentroids() const override;

    /**
     * @brief deleteElementCentroids
     */
    void deleteElementCentroids() override;

    /**
     * @brief getParametricCenter
     * @param pCoords
     */
    void getParametricCenter(double pCoords[3]) const override;

    /**
     * @brief getShapeFunctions
     * @param pCoords
     * @param shape
     */
    void getShapeFunctions(double pCoords[3], double* shape) const override;

    /**
     * @brief findDerivatives
     * @param field
     * @param derivatives
     */
    void findDerivatives(DoubleArrayType::Pointer field, DoubleArrayType::Pointer derivatives, Observable* observable = nullptr) override;

    /**
     * @brief getInfoString
     * @return Returns a formatted string that contains general infomation about
     * the instance of the object.
     */
    QString getInfoString(SIMPL::InfoStringFormat format) const override;

    /**
     * @brief writeGeometryToHDF5
     * @param parentId
     * @param writeXdmf
     * @return
     */
    int writeGeometryToHDF5(hid_t parentId, bool writeXdmf) const override;

    /**
     * @brief writeXdmf
     * @param out
     * @param dcName
     * @param hdfFileName
     * @return
     */
    int writeXdmf(QTextStream& out, QString dcName, QString hdfFileName) const override;

    /**
     * @brief readGeometryFromHDF5
     * @param parentId
     * @param preflight
     * @return
     */
    int readGeometryFromHDF5(hid_t parentId, bool preflight) override;

    /**
     * @brief deepCopy
     * @return
     */
    IGeometry::Pointer deepCopy(bool forceNoAllocate = false) const override;

    /**
     * @brief addOrReplaceAttributeMatrix
     */
    void addOrReplaceAttributeMatrix(const QString& name, AttributeMatrix::Pointer data) override;

// -----------------------------------------------------------------------------
// Inherited from IGeometry3D
// -----------------------------------------------------------------------------

    /**
     * @brief resizeVertexList
     * @param newNumVertices
     */
    void resizeVertexList(size_t newNumVertices) override;

    /**
     * @brief setVertices
     * @param vertices
     */
    void setVertices(SharedVertexList::Pointer vertices) override;

    /**
     * @brief getVertices
     * @return
     */
    SharedVertexList::Pointer getVertices() const override;

    /**
     * @brief setCoords
     * @param vertId
     * @param coords
     */
    void setCoords(size_t vertId, float coords[3]) override;

    /**
     * @brief getCoords
     * @param vertId
     * @param coords
     */
    void getCoords(size_t vertId, float coords[3]) const override;

    /**
     * @brief getVertexPointer
     * @param i
     * @return
     */
    float* getVertexPointer(size_t i) const override;

    /**
     * @brief getNumberOfVertices
     * @return
     */
    size_t getNumberOfVertices() const override;

    /**
     * @brief resizeEdgeList
     * @param newNumEdges
     */
    void resizeEdgeList(size_t newNumEdges) override;

    /**
     * @brief getEdges
     * @return
     */
    SharedEdgeList::Pointer getEdges() const override;

    /**
     * @brief setVerts
     * @param edgeId
     * @param verts
     */
    void setVertsAtEdge(size_t edgeId, size_t verts[2]) override;

    /**
     * @brief getVerts
     * @param edgeId
     * @param verts
     */
    void getVertsAtEdge(size_t edgeId, size_t verts[2]) const override;

    /**
     * @brief getVertCoordsAtEdge
     * @param edgeId
     * @param vert1
     * @param vert2
     */
    void getVertCoordsAtEdge(size_t edgeId, float vert1[3], float vert2[3]) const override;

    /**
     * @brief getEdgePointer
     * @param i
     * @return
     */
    size_t* getEdgePointer(size_t i) const override;

    /**
     * @brief getNumberOfEdges
     * @return
     */
    size_t getNumberOfEdges() const override;

    /**
     * @brief findElementEdges
     * @return
     */
    int findEdges() override;

    /**
     * @brief deleteElementEdges
     */
    void deleteEdges() override;

    /**
     * @brief findFaces
     * @return
     */
    int findFaces() override;

    /**
     * @brief deleteFaces
     */
    void deleteFaces() override;

    /**
     * @brief findUnsharedEdges
     */
    int findUnsharedEdges() override;

    /**
     * @brief getUnsharedEdges
     * @return
     */
    SharedEdgeList::Pointer getUnsharedEdges() const override;

    /**
     * @brief deleteUnsharedEdges
     */
    void deleteUnsharedEdges() override;

    /**
     * @brief findUnsharedFaces
     */
    int findUnsharedFaces() override;

    /**
     * @brief getUnsharedFaces
     * @return
     */
    SharedEdgeList::Pointer getUnsharedFaces() const override;

    /**
     * @brief deleteUnsharedFaces
     */
    void deleteUnsharedFaces() override;

  protected:

    HexahedralGeom();

    /**
     * @brief setElementsContainingVert
     * @param elementsContainingVert
     */
    void setElementsContainingVert(ElementDynamicList::Pointer elementsContainingVert) override;

    /**
     * @brief setElementNeighbors
     * @param elementNeighbors
     */
    void setElementNeighbors(ElementDynamicList::Pointer elementNeighbors) override;

    /**
     * @brief setElementCentroids
     * @param elementCentroids
     */
    void setElementCentroids(FloatArrayType::Pointer elementCentroids) override;

    /**
     * @brief setElementSizes
     * @param elementSizes
     */
    void setElementSizes(FloatArrayType::Pointer elementSizes) override;

    /**
     * @brief setEdges
     * @param edges
     */
    void setEdges(SharedEdgeList::Pointer edges) override;

    /**
     * @brief setUnsharedEdges
     * @param bEdgeList
     */
    void setUnsharedEdges(SharedEdgeList::Pointer bEdgeList) override;

    /**
     * @brief setUnsharedFaces
     * @param bFaceList
     */
    void setUnsharedFaces(SharedFaceList::Pointer bFaceList) override;

  private:
    SharedVertexList::Pointer m_VertexList;
    SharedEdgeList::Pointer m_EdgeList;
    SharedEdgeList::Pointer m_UnsharedEdgeList;
    SharedQuadList::Pointer m_QuadList;
    SharedQuadList::Pointer m_UnsharedQuadList;
    SharedHexList::Pointer m_HexList;
    ElementDynamicList::Pointer m_HexasContainingVert;
    ElementDynamicList::Pointer m_HexNeighbors;
    FloatArrayType::Pointer m_HexCentroids;
    FloatArrayType::Pointer m_HexSizes;

    friend class FindHexDerivativesImpl;

  public:
    HexahedralGeom(const HexahedralGeom&) = delete; // Copy Constructor Not Implemented
    HexahedralGeom(HexahedralGeom&&) = delete;      // Move Constructor Not Implemented
    HexahedralGeom& operator=(const HexahedralGeom&) = delete; // Copy Assignment Not Implemented
    HexahedralGeom& operator=(HexahedralGeom&&) = delete;      // Move Assignment Not Implemented
};


#endif /* _hexahedralgeom_h_ */

