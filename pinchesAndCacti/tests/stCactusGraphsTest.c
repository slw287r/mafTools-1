/*
 * stPinchGraphsTest.c
 *
 *  Created on: 11 Apr 2012
 *      Author: benedictpaten
 *
 * Copyright (C) 2009-2011 by Benedict Paten (benedictpaten@gmail.com)
 *
 * Released under the MIT license, see LICENSE.txt
 */

#include "CuTest.h"
#include "sonLib.h"
#include "stCactusGraphs.h"
#include <stdlib.h>

static stCactusGraph *g;
static int64_t nO1 = 1, nO2 = 2, nO3 = 3, nO4 = 4, nO5 = 5, nO6 = 6, nO7 = 7, nO8 = 8, nO9 = 9;
static stCactusNode *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;
static stCactusEdgeEnd *e12, *e21, *e23, *e32, *e13, *e31, *e24, *e42, *e11, *e11r, *e45, *e54, *e56, *e65, *e56r, *e65r, *e58, *e85, *e49,
        *e94, *e37, *e73, *e37r, *e73r;

static void teardown() {
    if (g != NULL) {
        stCactusGraph_destruct(g);
        g = NULL;
    }
}

static void *mergeNodeObjects(void *a, void *b) {
    int64_t i = *((int64_t *) a);
    int64_t j = *((int64_t *) b);
    return i > j ? b : a;
}

static void setup() {
    g = stCactusGraph_construct();
    n1 = stCactusNode_construct(g, &nO1);
    n2 = stCactusNode_construct(g, &nO2);
    n3 = stCactusNode_construct(g, &nO3);
    n4 = stCactusNode_construct(g, &nO4);
    n5 = stCactusNode_construct(g, &nO5);
    n6 = stCactusNode_construct(g, &nO6);
    n7 = stCactusNode_construct(g, &nO7);
    n8 = stCactusNode_construct(g, &nO8);
    n9 = stCactusNode_construct(g, &nO9);
    e12 = stCactusEdgeEnd_construct(g, n1, n2, &nO1, &nO2);
    e21 = stCactusEdgeEnd_getOtherEdgeEnd(e12);
    e23 = stCactusEdgeEnd_construct(g, n2, n3, &nO2, &nO3);
    e32 = stCactusEdgeEnd_getOtherEdgeEnd(e23);
    e13 = stCactusEdgeEnd_construct(g, n1, n3, &nO1, &nO3);
    e31 = stCactusEdgeEnd_getOtherEdgeEnd(e13);
    e24 = stCactusEdgeEnd_construct(g, n2, n4, &nO2, &nO4);
    e42 = stCactusEdgeEnd_getOtherEdgeEnd(e24);
    e11 = stCactusEdgeEnd_construct(g, n1, n1, &nO1, &nO1);
    e11r = stCactusEdgeEnd_getOtherEdgeEnd(e11);
    e45 = stCactusEdgeEnd_construct(g, n4, n5, &nO4, &nO5);
    e54 = stCactusEdgeEnd_getOtherEdgeEnd(e45);
    e56 = stCactusEdgeEnd_construct(g, n5, n6, &nO5, &nO6);
    e65 = stCactusEdgeEnd_getOtherEdgeEnd(e56);
    e56r = stCactusEdgeEnd_construct(g, n5, n6, &nO5, &nO6);
    e65r = stCactusEdgeEnd_getOtherEdgeEnd(e56r);
    e58 = stCactusEdgeEnd_construct(g, n5, n8, &nO5, &nO8);
    e85 = stCactusEdgeEnd_getOtherEdgeEnd(e58);
    e49 = stCactusEdgeEnd_construct(g, n4, n9, &nO4, &nO9);
    e94 = stCactusEdgeEnd_getOtherEdgeEnd(e49);
    e37 = stCactusEdgeEnd_construct(g, n3, n7, &nO3, &nO7);
    e73 = stCactusEdgeEnd_getOtherEdgeEnd(e37);
    e37r = stCactusEdgeEnd_construct(g, n3, n7, &nO3, &nO7);
    e73r = stCactusEdgeEnd_getOtherEdgeEnd(e37r);

    stCactusGraph_collapseToCactus(g, mergeNodeObjects, n1);
}

void invariantNodeTests(CuTest *testCase) {
    //Test the get object
    CuAssertPtrEquals(testCase, &nO1, stCactusNode_getObject(n1));
    CuAssertPtrEquals(testCase, &nO2, stCactusNode_getObject(n2));
    CuAssertPtrEquals(testCase, &nO3, stCactusNode_getObject(n3));
    CuAssertPtrEquals(testCase, &nO5, stCactusNode_getObject(n5));
    CuAssertPtrEquals(testCase, &nO6, stCactusNode_getObject(n6));
    CuAssertPtrEquals(testCase, &nO7, stCactusNode_getObject(n7));

    //Test iterator
    stCactusNodeEdgeEndIt it = stCactusNode_getEdgeEndIt(n1);
    CuAssertPtrEquals(testCase, e12, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e13, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e11, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e11r, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n3);
    CuAssertPtrEquals(testCase, e32, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e31, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e37, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e37r, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n5);
    CuAssertPtrEquals(testCase, e54, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e56, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e56r, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e58, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n6);
    CuAssertPtrEquals(testCase, e65, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e65r, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n7);
    CuAssertPtrEquals(testCase, e73, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e73r, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));
}

void testStCactusNode(CuTest *testCase) {
    setup();
    invariantNodeTests(testCase);

    //Test the get object
    CuAssertPtrEquals(testCase, &nO4, stCactusNode_getObject(n4));
    CuAssertPtrEquals(testCase, &nO8, stCactusNode_getObject(n8));
    CuAssertPtrEquals(testCase, &nO9, stCactusNode_getObject(n9));

    //Test iterator
    stCactusNodeEdgeEndIt it = stCactusNode_getEdgeEndIt(n2);
    CuAssertPtrEquals(testCase, e21, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e23, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e24, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n4);
    CuAssertPtrEquals(testCase, e42, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e45, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e49, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n8);
    CuAssertPtrEquals(testCase, e85, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    it = stCactusNode_getEdgeEndIt(n9);
    CuAssertPtrEquals(testCase, e94, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    teardown();
}

void testStCactusGraph(CuTest *testCase) {
    setup();

    //stCactusGraph_getNode
    CuAssertPtrEquals(testCase, n1, stCactusGraph_getNode(g, &nO1));
    CuAssertPtrEquals(testCase, n2, stCactusGraph_getNode(g, &nO2));
    CuAssertPtrEquals(testCase, n3, stCactusGraph_getNode(g, &nO3));
    CuAssertPtrEquals(testCase, n4, stCactusGraph_getNode(g, &nO4));
    CuAssertPtrEquals(testCase, n5, stCactusGraph_getNode(g, &nO5));
    CuAssertPtrEquals(testCase, n6, stCactusGraph_getNode(g, &nO6));
    CuAssertPtrEquals(testCase, n7, stCactusGraph_getNode(g, &nO7));
    CuAssertPtrEquals(testCase, n8, stCactusGraph_getNode(g, &nO8));
    CuAssertPtrEquals(testCase, n9, stCactusGraph_getNode(g, &nO9));
    CuAssertPtrEquals(testCase, NULL, stCactusGraph_getNode(g, testCase));

    //stCactusGraphNodeIterator_construct
    //stCactusGraphNodeIterator_getNext
    //stCactusGraphNodeIterator_destruct
    stCactusGraphNodeIt *nodeIt = stCactusGraphNodeIterator_construct(g);
    stCactusNode *n;
    stSortedSet *nodes = stSortedSet_construct();
    while ((n = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
        CuAssertTrue(testCase, stSortedSet_search(nodes, n) == NULL);
        CuAssertTrue(testCase,
                n == n1 || n == n2 || n == n3 || n == n4 || n == n5 || n == n6 || n == n7 || n == n8 || n == n9);
        stSortedSet_insert(nodes, n);
    }
    CuAssertIntEquals(testCase, 9, stSortedSet_size(nodes));
    stCactusGraphNodeIterator_destruct(nodeIt);
    stSortedSet_destruct(nodes);
    teardown();
}

static void invariantEdgeEndTests(CuTest *testCase) {
    //stCactusEdgeEnd_getObject
    CuAssertPtrEquals(testCase, &nO1, stCactusEdgeEnd_getObject(e12));
    CuAssertPtrEquals(testCase, &nO1, stCactusEdgeEnd_getObject(e13));
    CuAssertPtrEquals(testCase, &nO1, stCactusEdgeEnd_getObject(e11));
    CuAssertPtrEquals(testCase, &nO1, stCactusEdgeEnd_getObject(e11r));
    CuAssertPtrEquals(testCase, &nO2, stCactusEdgeEnd_getObject(e21));
    CuAssertPtrEquals(testCase, &nO2, stCactusEdgeEnd_getObject(e23));
    CuAssertPtrEquals(testCase, &nO2, stCactusEdgeEnd_getObject(e24));
    CuAssertPtrEquals(testCase, &nO3, stCactusEdgeEnd_getObject(e32));
    CuAssertPtrEquals(testCase, &nO3, stCactusEdgeEnd_getObject(e31));
    CuAssertPtrEquals(testCase, &nO3, stCactusEdgeEnd_getObject(e37));
    CuAssertPtrEquals(testCase, &nO3, stCactusEdgeEnd_getObject(e37r));
    CuAssertPtrEquals(testCase, &nO4, stCactusEdgeEnd_getObject(e42));
    CuAssertPtrEquals(testCase, &nO4, stCactusEdgeEnd_getObject(e45));
    CuAssertPtrEquals(testCase, &nO4, stCactusEdgeEnd_getObject(e49));
    CuAssertPtrEquals(testCase, &nO5, stCactusEdgeEnd_getObject(e54));
    CuAssertPtrEquals(testCase, &nO5, stCactusEdgeEnd_getObject(e56));
    CuAssertPtrEquals(testCase, &nO5, stCactusEdgeEnd_getObject(e56r));
    CuAssertPtrEquals(testCase, &nO5, stCactusEdgeEnd_getObject(e58));
    CuAssertPtrEquals(testCase, &nO6, stCactusEdgeEnd_getObject(e65r));
    CuAssertPtrEquals(testCase, &nO6, stCactusEdgeEnd_getObject(e65));
    CuAssertPtrEquals(testCase, &nO7, stCactusEdgeEnd_getObject(e73));
    CuAssertPtrEquals(testCase, &nO7, stCactusEdgeEnd_getObject(e73r));
    CuAssertPtrEquals(testCase, &nO8, stCactusEdgeEnd_getObject(e85));
    CuAssertPtrEquals(testCase, &nO9, stCactusEdgeEnd_getObject(e94));

    //stCactusEdgeEnd_getOtherEdgeEnd
    CuAssertPtrEquals(testCase, e21, stCactusEdgeEnd_getOtherEdgeEnd(e12));
    CuAssertPtrEquals(testCase, e31, stCactusEdgeEnd_getOtherEdgeEnd(e13));
    CuAssertPtrEquals(testCase, e11r, stCactusEdgeEnd_getOtherEdgeEnd(e11));
    CuAssertPtrEquals(testCase, e11, stCactusEdgeEnd_getOtherEdgeEnd(e11r));
    CuAssertPtrEquals(testCase, e12, stCactusEdgeEnd_getOtherEdgeEnd(e21));
    CuAssertPtrEquals(testCase, e32, stCactusEdgeEnd_getOtherEdgeEnd(e23));
    CuAssertPtrEquals(testCase, e42, stCactusEdgeEnd_getOtherEdgeEnd(e24));
    CuAssertPtrEquals(testCase, e23, stCactusEdgeEnd_getOtherEdgeEnd(e32));
    CuAssertPtrEquals(testCase, e13, stCactusEdgeEnd_getOtherEdgeEnd(e31));
    CuAssertPtrEquals(testCase, e73, stCactusEdgeEnd_getOtherEdgeEnd(e37));
    CuAssertPtrEquals(testCase, e73r, stCactusEdgeEnd_getOtherEdgeEnd(e37r));
    CuAssertPtrEquals(testCase, e24, stCactusEdgeEnd_getOtherEdgeEnd(e42));
    CuAssertPtrEquals(testCase, e54, stCactusEdgeEnd_getOtherEdgeEnd(e45));
    CuAssertPtrEquals(testCase, e94, stCactusEdgeEnd_getOtherEdgeEnd(e49));
    CuAssertPtrEquals(testCase, e45, stCactusEdgeEnd_getOtherEdgeEnd(e54));
    CuAssertPtrEquals(testCase, e65, stCactusEdgeEnd_getOtherEdgeEnd(e56));
    CuAssertPtrEquals(testCase, e65r, stCactusEdgeEnd_getOtherEdgeEnd(e56r));
    CuAssertPtrEquals(testCase, e85, stCactusEdgeEnd_getOtherEdgeEnd(e58));
    CuAssertPtrEquals(testCase, e56r, stCactusEdgeEnd_getOtherEdgeEnd(e65r));
    CuAssertPtrEquals(testCase, e56, stCactusEdgeEnd_getOtherEdgeEnd(e65));
    CuAssertPtrEquals(testCase, e37, stCactusEdgeEnd_getOtherEdgeEnd(e73));
    CuAssertPtrEquals(testCase, e37r, stCactusEdgeEnd_getOtherEdgeEnd(e73r));
    CuAssertPtrEquals(testCase, e58, stCactusEdgeEnd_getOtherEdgeEnd(e85));
    CuAssertPtrEquals(testCase, e49, stCactusEdgeEnd_getOtherEdgeEnd(e94));

    //stCactusEdgeEnd_getNode (those which don't change)
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getNode(e12));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getNode(e13));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getNode(e11));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getNode(e11r));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e21));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e23));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e24));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getNode(e32));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getNode(e31));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getNode(e37));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getNode(e37r));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getNode(e54));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getNode(e56));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getNode(e56r));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getNode(e58));
    CuAssertPtrEquals(testCase, n6, stCactusEdgeEnd_getNode(e65r));
    CuAssertPtrEquals(testCase, n6, stCactusEdgeEnd_getNode(e65));
    CuAssertPtrEquals(testCase, n7, stCactusEdgeEnd_getNode(e73));
    CuAssertPtrEquals(testCase, n7, stCactusEdgeEnd_getNode(e73r));

    //stCactusEdgeEnd_getOtherNode (those which don't change)
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e12));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getOtherNode(e13));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getOtherNode(e11));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getOtherNode(e11r));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getOtherNode(e21));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getOtherNode(e23));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e32));
    CuAssertPtrEquals(testCase, n1, stCactusEdgeEnd_getOtherNode(e31));
    CuAssertPtrEquals(testCase, n7, stCactusEdgeEnd_getOtherNode(e37));
    CuAssertPtrEquals(testCase, n7, stCactusEdgeEnd_getOtherNode(e37r));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e42));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getOtherNode(e45));
    CuAssertPtrEquals(testCase, n6, stCactusEdgeEnd_getOtherNode(e56));
    CuAssertPtrEquals(testCase, n6, stCactusEdgeEnd_getOtherNode(e56r));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getOtherNode(e65r));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getOtherNode(e65));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getOtherNode(e73));
    CuAssertPtrEquals(testCase, n3, stCactusEdgeEnd_getOtherNode(e73r));
    CuAssertPtrEquals(testCase, n5, stCactusEdgeEnd_getOtherNode(e85));
}

static void edgeEndTests(CuTest *testCase) {
    invariantEdgeEndTests(testCase);

    //stCactusEdgeEnd_getNode (those which change)
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getNode(e42));
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getNode(e45));
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getNode(e49));
    CuAssertPtrEquals(testCase, n8, stCactusEdgeEnd_getNode(e85));
    CuAssertPtrEquals(testCase, n9, stCactusEdgeEnd_getNode(e94));

    //stCactusEdgeEnd_getOtherNode (those which change)
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getOtherNode(e24));
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getOtherNode(e94));
    CuAssertPtrEquals(testCase, n8, stCactusEdgeEnd_getOtherNode(e58));
    CuAssertPtrEquals(testCase, n9, stCactusEdgeEnd_getOtherNode(e49));
    CuAssertPtrEquals(testCase, n4, stCactusEdgeEnd_getOtherNode(e54));
}

static void invariantChainStructureTests(CuTest *testCase) {
    //Now test the chain structure
    //stCactusEdgeEnd_getLink
    CuAssertPtrEquals(testCase, e13, stCactusEdgeEnd_getLink(e12));
    CuAssertPtrEquals(testCase, e12, stCactusEdgeEnd_getLink(e13));
    CuAssertPtrEquals(testCase, e11r, stCactusEdgeEnd_getLink(e11));
    CuAssertPtrEquals(testCase, e11, stCactusEdgeEnd_getLink(e11r));
    CuAssertPtrEquals(testCase, e23, stCactusEdgeEnd_getLink(e21));
    CuAssertPtrEquals(testCase, e21, stCactusEdgeEnd_getLink(e23));
    CuAssertPtrEquals(testCase, e31, stCactusEdgeEnd_getLink(e32));
    CuAssertPtrEquals(testCase, e32, stCactusEdgeEnd_getLink(e31));
    CuAssertPtrEquals(testCase, e37r, stCactusEdgeEnd_getLink(e37));
    CuAssertPtrEquals(testCase, e37, stCactusEdgeEnd_getLink(e37r));
    CuAssertPtrEquals(testCase, e56r, stCactusEdgeEnd_getLink(e56));
    CuAssertPtrEquals(testCase, e56, stCactusEdgeEnd_getLink(e56r));
    CuAssertPtrEquals(testCase, e65, stCactusEdgeEnd_getLink(e65r));
    CuAssertPtrEquals(testCase, e65r, stCactusEdgeEnd_getLink(e65));
    CuAssertPtrEquals(testCase, e73r, stCactusEdgeEnd_getLink(e73));
    CuAssertPtrEquals(testCase, e73, stCactusEdgeEnd_getLink(e73r));

    //stCactusEdgeEnd_getLinkOrientation (first of link edges)
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e12) != stCactusEdgeEnd_getLinkOrientation(e13));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e11) != stCactusEdgeEnd_getLinkOrientation(e11r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e23) != stCactusEdgeEnd_getLinkOrientation(e21));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e31) != stCactusEdgeEnd_getLinkOrientation(e32));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e37) != stCactusEdgeEnd_getLinkOrientation(e37r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e56) != stCactusEdgeEnd_getLinkOrientation(e56r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e65) != stCactusEdgeEnd_getLinkOrientation(e65r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e73) != stCactusEdgeEnd_getLinkOrientation(e73r));

    //stCactusEdgeEnd_getLinkOrientation (now of standard edges)
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e12) != stCactusEdgeEnd_getLinkOrientation(e21));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e11) != stCactusEdgeEnd_getLinkOrientation(e11r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e23) != stCactusEdgeEnd_getLinkOrientation(e32));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e31) != stCactusEdgeEnd_getLinkOrientation(e13));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e37) != stCactusEdgeEnd_getLinkOrientation(e73));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e56) != stCactusEdgeEnd_getLinkOrientation(e65));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e56r) != stCactusEdgeEnd_getLinkOrientation(e65r));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e37r) != stCactusEdgeEnd_getLinkOrientation(e73r));

    //stCactusEdgeEnd_isChainEnd
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e12));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e13));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e11));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e11r));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e21));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e23));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e32));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e31));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e37));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e37r));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e56));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e56r));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e58));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e65r));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e65));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e73));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e73r));
}

static void chainStructureTests(CuTest *testCase) {
    invariantChainStructureTests(testCase);
    //Check the chain structure of the bridge ends is uninitialised
    stCactusEdgeEnd *edgeEnds[] = { e24, e42, e45, e49, e54, e58, e85, e94 };
    for (int64_t i = 0; i < 8; i++) {
        CuAssertPtrEquals(testCase, NULL, stCactusEdgeEnd_getLink(edgeEnds[i]));
        CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_getLinkOrientation(edgeEnds[i]));
        CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(edgeEnds[i]));
    }
}

void testStCactusEdgeEnd(CuTest *testCase) {
    setup();
    edgeEndTests(testCase);
    chainStructureTests(testCase);
    teardown();
}

void testStCactusGraph_unmarkAndMarkCycles(CuTest *testCase) {
    setup();
    stCactusGraph_unmarkCycles(g);
    edgeEndTests(testCase);
    invariantNodeTests(testCase);

    //Now test the chain structure
    //stCactusEdgeEnd_getLink
    stCactusEdgeEnd *edgeEnds[] = { e12, e13, e11, e11r, e21, e23, e24, e32, e31, e37, e37r, e42, e45, e49, e54, e56, e56r, e58, e65, e65r,
            e73, e73r, e85, e94 };

    for (int64_t i = 0; i < 24; i++) {
        CuAssertPtrEquals(testCase, NULL, stCactusEdgeEnd_getLink(edgeEnds[i]));
        CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_getLinkOrientation(edgeEnds[i]));
        CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(edgeEnds[i]));
    }

    stCactusGraph_markCycles(g, n1);
    edgeEndTests(testCase);
    chainStructureTests(testCase);
    invariantNodeTests(testCase);

    teardown();
}

void testStCactusGraph_collapseBridges(CuTest *testCase) {
    setup();
    stCactusGraph_collapseBridges(g, n1, mergeNodeObjects);
    n2 = stCactusGraph_getNode(g, &nO2);

    invariantEdgeEndTests(testCase);
    invariantChainStructureTests(testCase);
    invariantNodeTests(testCase);

    //stCactusEdgeEnd_getNode (those which change)
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e42));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e45));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e49));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e85));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getNode(e94));

    //stCactusEdgeEnd_getOtherNode (those which change)
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e24));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e94));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e58));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e49));
    CuAssertPtrEquals(testCase, n2, stCactusEdgeEnd_getOtherNode(e54));

    //Check chains
    //stCactusEdgeEnd_getLink
    CuAssertPtrEquals(testCase, e42, stCactusEdgeEnd_getLink(e24));
    CuAssertPtrEquals(testCase, e24, stCactusEdgeEnd_getLink(e42));
    CuAssertPtrEquals(testCase, e85, stCactusEdgeEnd_getLink(e45));
    CuAssertPtrEquals(testCase, e94, stCactusEdgeEnd_getLink(e49));
    CuAssertPtrEquals(testCase, e58, stCactusEdgeEnd_getLink(e54));
    CuAssertPtrEquals(testCase, e54, stCactusEdgeEnd_getLink(e58));
    CuAssertPtrEquals(testCase, e45, stCactusEdgeEnd_getLink(e85));
    CuAssertPtrEquals(testCase, e49, stCactusEdgeEnd_getLink(e94));

    //stCactusEdgeEnd_getLinkOrientation
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e42) != stCactusEdgeEnd_getLinkOrientation(e24));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e85) != stCactusEdgeEnd_getLinkOrientation(e45));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e94) != stCactusEdgeEnd_getLinkOrientation(e49));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e58) != stCactusEdgeEnd_getLinkOrientation(e54));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e54) != stCactusEdgeEnd_getLinkOrientation(e45));
    CuAssertTrue(testCase, stCactusEdgeEnd_getLinkOrientation(e58) != stCactusEdgeEnd_getLinkOrientation(e85));

    //stCactusEdgeEnd_isChainEnd
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e24));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e42));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e45));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e49));
    CuAssertIntEquals(testCase, 0, stCactusEdgeEnd_isChainEnd(e54));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e85));
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e94));

    //Check edge end it.
    stCactusNodeEdgeEndIt it = stCactusNode_getEdgeEndIt(n2);
    CuAssertPtrEquals(testCase, e21, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e23, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e24, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e42, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e45, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e49, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e94, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, e85, stCactusNodeEdgeEndIt_getNext(&it));
    CuAssertPtrEquals(testCase, NULL, stCactusNodeEdgeEndIt_getNext(&it));

    //Check graph node it.
    stCactusGraphNodeIt *nodeIt = stCactusGraphNodeIterator_construct(g);
    stCactusNode *n;
    stSortedSet *nodes = stSortedSet_construct();
    while ((n = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
        CuAssertTrue(testCase, stSortedSet_search(nodes, n) == NULL);
        CuAssertTrue(testCase, n == n1 || n == n2 || n == n3 || n == n5 || n == n6 || n == n7);
        stSortedSet_insert(nodes, n);
    }
    CuAssertIntEquals(testCase, 6, stSortedSet_size(nodes));
    stCactusGraphNodeIterator_destruct(nodeIt);
    stSortedSet_destruct(nodes);
    teardown();
}

bool endIsNotInChain(stCactusEdgeEnd *edgeEnd, void *endsNotInChainSet) {
    return stSet_search(endsNotInChainSet, edgeEnd) != NULL;
}

void testStCactusGraph_breakChainsByEndsNotInChains(CuTest *testCase) {
    setup();
    stCactusGraph_collapseBridges(g, n1, mergeNodeObjects);
    stSet *endsNotInChainSet = stSet_construct();
    stSet_insert(endsNotInChainSet, e54);
    stCactusGraph_breakChainsByEndsNotInChains(g, n1, mergeNodeObjects, endIsNotInChain, endsNotInChainSet);
    //Check graph.
    CuAssertIntEquals(testCase, 1, stCactusEdgeEnd_isChainEnd(e54));
    //cleanup
    stSet_destruct(endsNotInChainSet);
    teardown();
}

stSet *getRandomSetOfEdgeEnds(stCactusGraph *g, double probabilityOfInclusion) {
    stSet *edgeEnds = stSet_construct();
    stCactusGraphNodeIt *nIt = stCactusGraphNodeIterator_construct(g);
    stCactusNode *n;
    while((n = stCactusGraphNodeIterator_getNext(nIt)) != NULL) {
        stCactusNodeEdgeEndIt eIt = stCactusNode_getEdgeEndIt(n);
        stCactusEdgeEnd *e;
        while((e = stCactusNodeEdgeEndIt_getNext(&eIt)) != NULL) {
            if(st_random() < probabilityOfInclusion) {
                assert(stSet_search(edgeEnds, e) == NULL);
                stSet_insert(edgeEnds, e);
            }
        }
    }
    stCactusGraphNodeIterator_destruct(nIt);
    return edgeEnds;
}

struct RandomCactusGraph {
    int64_t nodeNumber;
    int64_t edgeNumber;
    stCactusGraph *cactusGraph;
    stCactusNode *startNode;
    stList *nodeObjects;
    stSortedSet *edgeEnds;
};

static struct RandomCactusGraph *getRandomCactusGraph(bool multipleComponents) {
    struct RandomCactusGraph *rGraph = st_malloc(sizeof(struct RandomCactusGraph));

    // Randomly select the size and cardinality of the graph
    rGraph->nodeNumber = st_randomInt(0, 100); //1000);
    rGraph->edgeNumber = rGraph->nodeNumber > 0 ? st_randomInt(0, 200) : 0; //1000) : 0;
    st_logInfo("We have %" PRIi64 " edges and %" PRIi64 " nodes in random test\n",
            rGraph->edgeNumber, rGraph->nodeNumber);

    // The graph
    rGraph->cactusGraph = stCactusGraph_construct();

    // External containers for tracking nodes and edges
    rGraph->nodeObjects = stList_construct3(0, free);
    rGraph->edgeEnds = stSortedSet_construct();

    // Create the nodes
    for (int64_t i = 0; i < rGraph->nodeNumber; i++) {
        int64_t *j = st_malloc(sizeof(int64_t));
        j[0] = i;
        stCactusNode_construct(rGraph->cactusGraph, j);
        stList_append(rGraph->nodeObjects, j);
    }

    // Start node
    rGraph->startNode = rGraph->nodeNumber > 0 ? stCactusGraph_getNode(rGraph->cactusGraph,
            st_randomChoice(rGraph->nodeObjects)) : NULL;

    // Create the edges
    if (rGraph->nodeNumber > 0) {

        //If not multipleComponents, edge construction ensures there is just one component containing edges.
        stList *includedNodeObjects = stList_construct();
        assert(rGraph->startNode != NULL);
        stList_append(includedNodeObjects, stCactusNode_getObject(rGraph->startNode));

        for (int64_t i = 0; i < rGraph->edgeNumber; i++) {
            void *nodeObject1 = st_randomChoice(multipleComponents ? rGraph->nodeObjects : includedNodeObjects);
            void *nodeObject2 = st_randomChoice(rGraph->nodeObjects);
            if (!stList_contains(includedNodeObjects, nodeObject2)) {
                stList_append(includedNodeObjects, nodeObject2);
            }
            stCactusNode *node1 = stCactusGraph_getNode(rGraph->cactusGraph, nodeObject1);
            assert(node1 != NULL);
            stCactusNode *node2 = stCactusGraph_getNode(rGraph->cactusGraph, nodeObject2);
            assert(node2 != NULL);
            stCactusEdgeEnd *edgeEnd = stCactusEdgeEnd_construct(rGraph->cactusGraph, node1, node2, nodeObject1, nodeObject2);
            stSortedSet_insert(rGraph->edgeEnds, edgeEnd);
            stSortedSet_insert(rGraph->edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd));
        }

        stList_destruct(includedNodeObjects);
    }

    // Collapse to cactus
    stCactusGraph_collapseToCactus(rGraph->cactusGraph, mergeNodeObjects, rGraph->startNode);

    return rGraph;
}

static void destroyRandomCactusGraph(struct RandomCactusGraph *rGraph) {
    stCactusGraph_destruct(rGraph->cactusGraph);
    stSortedSet_destruct(rGraph->edgeEnds);
    stList_destruct(rGraph->nodeObjects);
    free(rGraph);
}

void testStCactusGraph_randomTest(CuTest *testCase) {
    // Creates problem instances, then checks graph is okay by checking every edge
    // is properly connected, with right number of nodes and that everyone is in a chain
    for (int64_t test = 0; test < 1000; test++) {

        // Make a random graph
        struct RandomCactusGraph *rGraph = getRandomCactusGraph(0);

        // Parameters for testing
        int64_t longChain = st_randomInt(2, 10);
        int64_t chainLengthForBigFlower = st_randomInt(0, 20);

        stSet *edgeEndsNotInChainSet = NULL;

        // Perform manipulations
        if(rGraph->nodeNumber > 0) {
            stCactusGraph_collapseBridges(rGraph->cactusGraph, rGraph->startNode, mergeNodeObjects);
            edgeEndsNotInChainSet = getRandomSetOfEdgeEnds(rGraph->cactusGraph, st_random());
            rGraph->startNode = stCactusGraph_breakChainsByEndsNotInChains(rGraph->cactusGraph, rGraph->startNode, mergeNodeObjects, endIsNotInChain, edgeEndsNotInChainSet);
            stSet_destruct(stCactusGraph_collapseLongChainsOfBigFlowers(rGraph->cactusGraph, rGraph->startNode, chainLengthForBigFlower, longChain, mergeNodeObjects, 1));
        }

        //Now iterate through nodes and check chains
        stCactusGraphNodeIt *nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        stCactusNode *node;
        stSortedSet *nodesInFinalGraph = stSortedSet_construct();
        while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            //Check node has valid object
            CuAssertTrue(testCase, stList_contains(rGraph->nodeObjects, stCactusNode_getObject(node)));
            CuAssertTrue(testCase, stSortedSet_search(nodesInFinalGraph, node) == NULL);
            stSortedSet_insert(nodesInFinalGraph, node);
        }
        stCactusGraphNodeIterator_destruct(nodeIt);

        //Check basic connectivity.
        nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        int64_t edgeEndNumber = 0;
        while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            CuAssertPtrEquals(testCase, node, stSortedSet_search(nodesInFinalGraph, node));
            stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(node);
            stCactusEdgeEnd *edgeEnd;
            while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt)) != NULL) {
                edgeEndNumber++;
                //Check node connectivity
                CuAssertPtrEquals(testCase, edgeEnd, stSortedSet_search(rGraph->edgeEnds, edgeEnd));
                CuAssertPtrEquals(testCase, node, stCactusEdgeEnd_getNode(edgeEnd));
                //Check other edge end connectivity
                stCactusEdgeEnd *otherEdgeEnd = stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd);
                CuAssertPtrEquals(testCase, otherEdgeEnd, stSortedSet_search(rGraph->edgeEnds, otherEdgeEnd));
                CuAssertPtrEquals(testCase, edgeEnd, stCactusEdgeEnd_getOtherEdgeEnd(otherEdgeEnd));
                CuAssertTrue(testCase,
                        stSortedSet_search(nodesInFinalGraph, stCactusEdgeEnd_getNode(otherEdgeEnd)) != NULL);
                CuAssertTrue(testCase,
                        stCactusEdgeEnd_getLinkOrientation(edgeEnd) != stCactusEdgeEnd_getLinkOrientation(otherEdgeEnd));
                CuAssertPtrEquals(testCase, stCactusEdgeEnd_getOtherNode(edgeEnd),
                        stCactusEdgeEnd_getNode(otherEdgeEnd));
                //Check chain connectivity
                stCactusEdgeEnd *linkedEdgeEnd = stCactusEdgeEnd_getLink(edgeEnd);
                CuAssertPtrEquals(testCase, linkedEdgeEnd, stSortedSet_search(rGraph->edgeEnds, linkedEdgeEnd));
                CuAssertPtrEquals(testCase, node, stCactusEdgeEnd_getNode(linkedEdgeEnd));
                CuAssertPtrEquals(testCase, edgeEnd, stCactusEdgeEnd_getLink(linkedEdgeEnd));
                CuAssertTrue(testCase, stCactusEdgeEnd_isChainEnd(edgeEnd) == stCactusEdgeEnd_isChainEnd(linkedEdgeEnd));
                CuAssertTrue(
                        testCase,
                        stCactusEdgeEnd_getLinkOrientation(edgeEnd)
                        != stCactusEdgeEnd_getLinkOrientation(linkedEdgeEnd));
                //Properties that must be true if chain is a cycle
                CuAssertTrue(testCase, linkedEdgeEnd != edgeEnd);
                CuAssertTrue(testCase, otherEdgeEnd != edgeEnd);
            }
        }
        stCactusGraphNodeIterator_destruct(nodeIt);
        CuAssertIntEquals(testCase, rGraph->edgeNumber * 2, edgeEndNumber);
        //Check each chain is a simple cycle.
        nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(node);
            stCactusEdgeEnd *edgeEnd;
            int64_t linkEnds = 0;
            int64_t totalEnds = 0;
            while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt)) != NULL) {
                totalEnds++;
                linkEnds += stCactusEdgeEnd_isChainEnd(edgeEnd) ? 0 : 1;
                stSortedSet *nodesOnCycle = stSortedSet_construct();
                stSortedSet_insert(nodesOnCycle, stCactusEdgeEnd_getNode(edgeEnd));
                stCactusEdgeEnd *chainEdgeEnd = edgeEnd;
                bool chainEnd = 0;
                while (1) {
                    chainEdgeEnd = stCactusEdgeEnd_getLink(stCactusEdgeEnd_getOtherEdgeEnd(chainEdgeEnd));
                    if (stCactusEdgeEnd_isChainEnd(chainEdgeEnd)) {
                        CuAssertTrue(testCase, chainEnd == 0);
                        chainEnd = 1;
                    }
                    if (chainEdgeEnd == edgeEnd) {
                        break;
                    }
                    CuAssertPtrEquals(testCase, NULL,
                            stSortedSet_search(nodesOnCycle, stCactusEdgeEnd_getNode(chainEdgeEnd)));
                    stSortedSet_insert(nodesOnCycle, stCactusEdgeEnd_getNode(chainEdgeEnd));
                }
                CuAssertTrue(testCase, chainEnd);
                stSortedSet_destruct(nodesOnCycle);
            }
            CuAssertTrue(testCase, linkEnds == 0 || linkEnds == 2);
            if(node == rGraph->startNode) {
                CuAssertIntEquals(testCase, 0, linkEnds);
            }
            else if(totalEnds > 0) {
                CuAssertIntEquals(testCase, 2, linkEnds);
            }
        }
        stCactusGraphNodeIterator_destruct(nodeIt);

        //Check no long chains of big flowers
        nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            if (stCactusNode_getTotalEdgeLengthOfFlower(node) > chainLengthForBigFlower && stCactusNode_getChainNumber(node) > 1) {
                stCactusNodeEdgeEndIt edgeIt = stCactusNode_getEdgeEndIt(node);
                stCactusEdgeEnd *edgeEnd;
                while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeIt)) != NULL) {
                    if (stCactusEdgeEnd_isChainEnd(edgeEnd)) {
                        //st_uglyf("%" PRIi64 " %" PRIi64 " %" PRIi64 " %" PRIi64 " %" PRIi64 "\n", chainLengthForBigFlower, longChain, stCactusNode_getTotalEdgeLengthOfFlower(node), stCactusNode_getChainNumber(node), stCactusEdgeEnd_getChainLength(edgeEnd));
                        CuAssertTrue(testCase, stCactusEdgeEnd_getChainLength(edgeEnd) <= longChain);
                    }
                }
            }
        }
        stCactusGraphNodeIterator_destruct(nodeIt);

        //Check no chains contain links including members of edgeEndsNotInChainSet (this does not check that chains are maximal).
        nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            stCactusNodeEdgeEndIt edgeIt = stCactusNode_getEdgeEndIt(node);
            stCactusEdgeEnd *edgeEnd;
            while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeIt)) != NULL) {
                if (!stCactusEdgeEnd_isChainEnd(edgeEnd)) {
                    //st_uglyf("%" PRIi64 " %" PRIi64 " %" PRIi64 " %" PRIi64 " %" PRIi64 "\n", chainLengthForBigFlower, longChain, stCactusNode_getTotalEdgeLengthOfFlower(node), stCactusNode_getChainNumber(node), stCactusEdgeEnd_getChainLength(edgeEnd));
                    CuAssertTrue(testCase, stSet_search(edgeEndsNotInChainSet, edgeEnd) == NULL);
                }
            }
        }
        stCactusGraphNodeIterator_destruct(nodeIt);

        // Cleanup
        destroyRandomCactusGraph(rGraph);
        stSortedSet_destruct(nodesInFinalGraph);
        if(edgeEndsNotInChainSet != NULL) {
            stSet_destruct(edgeEndsNotInChainSet);
        }
    }
}

static void makeComponent(stCactusNode *cactusNode, stSet *component, bool ignoreBridges) {
    if(stSet_search(component, cactusNode) == NULL) {
        stSet_insert(component, cactusNode);

        // Recursively add connected nodes
        stCactusNodeEdgeEndIt edgeIterator = stCactusNode_getEdgeEndIt(cactusNode);
        stCactusEdgeEnd *edgeEnd;
        while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeIterator))) {
            assert(cactusNode == stCactusEdgeEnd_getNode(edgeEnd));
            if(!ignoreBridges || stCactusEdgeEnd_getLink(edgeEnd) != NULL) {
                makeComponent(stCactusEdgeEnd_getNode(stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd)), component, ignoreBridges);
            }
        }
    }
}

void testStCactusGraph_getComponents(CuTest *testCase) {
    // Creates problem instances, then checks resulting component set.
    for (int64_t test = 0; test < 1000; test++) {
        // Make a random graph
        struct RandomCactusGraph *rGraph = getRandomCactusGraph(1);

        // Get components
        stList *components = stCactusGraph_getComponents(rGraph->cactusGraph, 0);

        // Get map of nodes to components
        stHash *cactusNodesToComponents = stCactusGraphComponents_getNodesToComponentsMap(components);

        // Check every node in the graph is in a component
        stCactusGraphNodeIt *nodeIt = stCactusGraphNodeIterator_construct(rGraph->cactusGraph);
        stCactusNode *cactusNode;
        while((cactusNode = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
            stSet *component = stHash_search(cactusNodesToComponents, cactusNode);
            CuAssertTrue(testCase, component != NULL);
            CuAssertTrue(testCase, stSet_search(component, cactusNode) == cactusNode);
        }
        stCactusGraphNodeIterator_destruct(nodeIt);

        int64_t totalNodeNumber = 0; // Counter to check that each node belongs to just one component

        // For each component, check its connectivity
        for(int64_t i=0; i<stList_length(components); i++) {
            stSet *component = stList_get(components, i);
            totalNodeNumber += stSet_size(component);

            // Must have non-zero size
            CuAssertTrue(testCase, stSet_size(component) > 0);

            // Make an equivalent component by DFS
            stSet *component2 = stSet_construct();
            stSetIterator *componentIt = stSet_getIterator(component);
            while((cactusNode = stSet_getNext(componentIt)) != NULL) {
                makeComponent(cactusNode, component2, 0);
            }
            stSet_destructIterator(componentIt);

            // Check components are equal
            CuAssertTrue(testCase, stSet_equals(component, component2));

            // Cleanup
            stSet_destruct(component2);
        }
        CuAssertIntEquals(testCase, totalNodeNumber, stCactusGraph_getNodeNumber(rGraph->cactusGraph));

        // Cleanup
        stHash_destruct(cactusNodesToComponents);
        destroyRandomCactusGraph(rGraph);
        stList_destruct(components);
    }

}

static stSet *getBridgeEnds(CuTest *testCase, struct RandomCactusGraph *rGraph) {
    /*
     * Get set of bridge edge ends in a cactus graph.
     */
    stSet *bridgeEdgeEnds = stSet_construct();
    CuAssertIntEquals(testCase, stSortedSet_size(rGraph->edgeEnds), 2*rGraph->edgeNumber);
    stSortedSetIterator *edgeEndIt = stSortedSet_getIterator(rGraph->edgeEnds);
    stCactusEdgeEnd *edgeEnd;
    while((edgeEnd = stSortedSet_getNext(edgeEndIt)) != NULL) {
        if(stCactusEdgeEnd_getLink(edgeEnd) == NULL) { // Is a bridge
            stSet_insert(bridgeEdgeEnds, edgeEnd);
        }
    }
    stSortedSet_destructIterator(edgeEndIt);
    CuAssertTrue(testCase, stSet_size(bridgeEdgeEnds)%2 == 0); // Must be even
    return bridgeEdgeEnds;
}

static stSet *getIncidentBridgeEdgeEnds(stSet *cactusNodes) {
    /*
     * Gets set of bridge edge ends incident with nodes in cactusNodes.
     */
    stSet *bridgeEdgeEnds = stSet_construct();
    stSetIterator *nodeIt = stSet_getIterator(cactusNodes);
    stCactusNode *cactusNode;
    while((cactusNode = stSet_getNext(nodeIt)) != NULL) {
        stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(cactusNode);
        stCactusEdgeEnd *edgeEnd;
        while((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt))) {
            if(stCactusEdgeEnd_getLink(edgeEnd) == NULL) {
                stSet_insert(bridgeEdgeEnds, edgeEnd);
            }
        }
    }
    stSet_destructIterator(nodeIt);
    return bridgeEdgeEnds;
}

static bool hasBridgeInSubtree(stCactusEdgeEnd *edgeEnd, stSet *seen) {
    stCactusNode *cactusNode = stCactusEdgeEnd_getNode(edgeEnd);
    if(stSet_search(seen, cactusNode) != NULL) {
        return 0;
    }
    stSet_insert(seen, cactusNode);
    stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(cactusNode);
    while((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt)) != NULL) {
        // If is a bridge then return true
        if(stCactusEdgeEnd_getLink(edgeEnd) == NULL) {
            return 1;
        }
        // Recurse to search for a bridge
        if(hasBridgeInSubtree(stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd), seen)) {
            return 1;
        }
    }
    return 0;
}

static stSet *getNodesOnPathsBetweenBridgeEdgeEnds(stSet *cactusNodes) {
    /*
     * Gets set of nodes that project to paths in the cactus tree connecting the given set of bridge edge ends.
     */

    stSet *connectedCactusNodes = stSet_construct();

    // For each cactus node
    stSetIterator *setIt = stSet_getIterator(cactusNodes);
    stCactusNode *cactusNode;
    while((cactusNode = stSet_getNext(setIt)) != NULL) {

        // Counter of connected chains/bridges
        int64_t connectedBridges = 0;
        int64_t connectedChains = 0;

        // For each edge
        stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(cactusNode);
        stCactusEdgeEnd *edgeEnd;
        while((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt)) != NULL) {

            // If bridge increase the connected bridges count
            if(stCactusEdgeEnd_getLink(edgeEnd) == NULL) {
                connectedBridges++;
            }
            else if(stCactusEdgeEnd_getLinkOrientation(edgeEnd)) {
                // Else recurse
                stSet *seen = stSet_construct();
                stSet_insert(seen, cactusNode);
                if(hasBridgeInSubtree(stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd), seen)) {
                    connectedChains++;
                }
                stSet_destruct(seen);
            }
        }

        if(connectedBridges > 0 || connectedChains > 1) {
            stSet_insert(connectedCactusNodes, cactusNode);
        }
    }

    // Cleanup
    stSet_destructIterator(setIt);

    return connectedCactusNodes;
}

void testStCactusGraph_getBridgeGraphs(CuTest *testCase) {
    // Creates problem instances, then checks resulting component set.
    for (int64_t test = 0; test < 1000; test++) {
        // Make a random graph
        struct RandomCactusGraph *rGraph = getRandomCactusGraph(1);

        stSet *bridgeEnds = getBridgeEnds(testCase, rGraph);
        int64_t totalBridgeEndsSeen = 0; // Counter used to check we've seen all the bridges
        int64_t totalCatusNodesSeen = 0; // Ditto, for cactus nodes

        // Get components
        stList *components = stCactusGraph_getComponents(rGraph->cactusGraph, 0);

        // For each component, build the bridge graph and check it
        for(int64_t i=0; i<stList_length(components); i++) {
            stSet *component = stList_get(components, i);
            CuAssertTrue(testCase, stSet_size(component) > 0);
            stCactusNode *cactusNode = stSet_peek(component);

            stBridgeGraph *bridgeGraph = stBridgeGraph_getBridgeGraph(cactusNode);

            // Check bridge graph

            // For each node in the bridge graph
            for(int64_t j=0; j<stList_length(bridgeGraph->bridgeNodes); j++) {
                stBridgeNode *bridgeNode = stList_get(bridgeGraph->bridgeNodes, j);

                // Check every incident edge in the bridge graph is a bridge
                CuAssertTrue(testCase, stSet_isSubset(bridgeEnds, bridgeNode->bridgeEnds));

                // Increment the number of bridges seen
                totalBridgeEndsSeen += stSet_size(bridgeNode->bridgeEnds);

                // Check set of cactus nodes that project to bridge node are in one bridgeless component
                stSet *bridgelessComponent = stSet_construct();
                makeComponent(stSet_peek(bridgeNode->cactusNodes), bridgelessComponent, 1);
                CuAssertTrue(testCase, stSet_equals(bridgelessComponent, bridgeNode->cactusNodes));
                stSet_destruct(bridgelessComponent);

                // Increment the number of cactus nodes seen
                totalCatusNodesSeen += stSet_size(bridgeNode->cactusNodes);

                // Check the bridges incident with cactus nodes in the bridgeless component
                // are equal to the set of bridges in the component
                stSet *bridgeEnds = getIncidentBridgeEdgeEnds(bridgeNode->cactusNodes);
                CuAssertTrue(testCase, stSet_equals(bridgeEnds, bridgeNode->bridgeEnds));
                stSet_destruct(bridgeEnds);

                // Check "connectedCactusNodes", the set of nodes connecting the bridge edge ends
                stSet *connectedCactusNodes = getNodesOnPathsBetweenBridgeEdgeEnds(bridgeNode->cactusNodes);
                //st_uglyf(" Connected nodes: %" PRIi64 " bridge node connected nodes: %" PRIi64 " bridge ends: %" PRIi64 " \n", stSet_size(connectedCactusNodes), stSet_size(bridgeNode->connectedCactusNodes), stSet_size(bridgeNode->bridgeEnds));
                //stBridgeNode_print(bridgeNode);
                CuAssertTrue(testCase, stSet_equals(connectedCactusNodes, bridgeNode->connectedCactusNodes));
                stSet_destruct(connectedCactusNodes);

                // Check the edges of the bridge graph
                // Check equal number of bridge ends and connected nodes
                CuAssertIntEquals(testCase, stSet_size(bridgeNode->bridgeEnds),
                        stList_length(bridgeNode->connectedNodes));

                // For each connected bridge node
                for(int64_t j=0; j<stList_length(bridgeNode->connectedNodes); j++) {
                    stBridgeNode *connectedBridgeNode = stList_get(bridgeNode->connectedNodes, j);

                    // Check there is a back edge
                    CuAssertTrue(testCase, stList_contains(connectedBridgeNode->connectedNodes, bridgeNode));

                    // Check for each connected bridge node there is a bridge edge connecting the components
                    stSetIterator *edgeEndIt = stSet_getIterator(bridgeNode->bridgeEnds);
                    stCactusEdgeEnd *edgeEnd;
                    bool gotLink = 0;
                    while((edgeEnd = stSet_getNext(edgeEndIt)) != NULL) {
                        if(stSet_search(connectedBridgeNode->bridgeEnds,
                                stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd)) != NULL) {
                            CuAssertTrue(testCase, !gotLink);
                            gotLink = 1;
                        }
                    }
                    stSet_destructIterator(edgeEndIt);
                    CuAssertTrue(testCase, gotLink);
                }
            }
            stBridgeGraph_destruct(bridgeGraph);
        }

        // Check we've accounted for all the bridges / nodes
        CuAssertIntEquals(testCase, stSet_size(bridgeEnds), totalBridgeEndsSeen);
        CuAssertIntEquals(testCase, stCactusGraph_getNodeNumber(rGraph->cactusGraph), totalCatusNodesSeen);

        // Cleanup
        destroyRandomCactusGraph(rGraph);
        stList_destruct(components);
        stSet_destruct(bridgeEnds);
    }
}

static void checkSnarlChain(CuTest *testCase, stList *chain, bool hasParent);

static void checkSnarl(CuTest *testCase, stSnarl *snarl, bool hasParent);

static void checkUnarySnarl(CuTest *testCase, stSnarl *snarl);

static void checkNestedSnarls(CuTest *testCase, stSnarl *snarl) {
	// Check nested unary snarls
	for(int64_t i=0; i<stList_length(snarl->unarySnarls); i++) {
		checkUnarySnarl(testCase, stList_get(snarl->unarySnarls, i));
	}

	// Check nested chains
	for(int64_t i=0; i<stList_length(snarl->chains); i++) {
		checkSnarlChain(testCase, stList_get(snarl->chains, i), snarl);
	}
}

static void checkUnarySnarl(CuTest *testCase, stSnarl *snarl) {
	// Check has just one boundary
	CuAssertTrue(testCase, snarl->edgeEnd1 == snarl->edgeEnd2);

	// Check is bridge
	CuAssertTrue(testCase, stCactusEdgeEnd_getLink(snarl->edgeEnd1) == NULL);

	checkNestedSnarls(testCase, snarl); // Recursively check children
}

static void checkSnarl(CuTest *testCase, stSnarl *snarl, bool hasParent) {
	// Check not a unary snarl
	CuAssertTrue(testCase, snarl->edgeEnd1 != snarl->edgeEnd2);

    // Check that the removal of both edges disconnects the cactus

    if(stCactusEdgeEnd_getLink(snarl->edgeEnd1) == NULL) { // Is a bridge
        // The other end must also be a bridge for the graph to be disconnected by their removal
        CuAssertTrue(testCase, stCactusEdgeEnd_getLink(snarl->edgeEnd2) == NULL);

        // Can not be nested
        CuAssertTrue(testCase, !hasParent);
    }
    else { // Is in a chain
        // Other end can not be a bridge
        CuAssertTrue(testCase, stCactusEdgeEnd_getLink(snarl->edgeEnd2) != NULL);

        // As both are in a chain, must be connected
        CuAssertTrue(testCase, stCactusEdgeEnd_getLink(snarl->edgeEnd1) == snarl->edgeEnd2);
        CuAssertTrue(testCase, stCactusEdgeEnd_getLink(snarl->edgeEnd2) == snarl->edgeEnd1);
        CuAssertTrue(testCase, stCactusEdgeEnd_getNode(snarl->edgeEnd1) == stCactusEdgeEnd_getNode(snarl->edgeEnd2));
    }

    checkNestedSnarls(testCase, snarl); // Recursively check children
}

static void checkSnarlChain(CuTest *testCase, stList *chain, bool hasParent) {
	// Check chain is not empty
	CuAssertTrue(testCase, stList_length(chain) > 0);

	// For each snarl in chain
	for(int64_t j=0; j<stList_length(chain); j++) {
		stSnarl *snarl = stList_get(chain, j);

		// If there is a preceding element in the chain, check that the ends match up
		if(j > 0) {
			stSnarl *pSnarl = stList_get(chain, j-1);
			CuAssertTrue(testCase, stCactusEdgeEnd_getOtherEdgeEnd(pSnarl->edgeEnd2) == snarl->edgeEnd1);
		}

		// Recursively check the nested snarl
		checkSnarl(testCase, snarl, hasParent);
	}
}

static void checkSnarlDecomposition(CuTest *testCase, stSnarlDecomposition *snarls, stList *telomeres) {

	// Check we got the expected number of top level chains
	CuAssertIntEquals(testCase, stList_length(telomeres)/2,
	    stList_length(snarls->topLevelChains) + stList_length(snarls->topLevelUnarySnarls));

	// For each top level chain / unary snarl
	int64_t i=0, j=0;
    for(int64_t k=0; k<stList_length(telomeres); k+=2) {
    	stCactusEdgeEnd *edgeEnd1 = stList_get(telomeres, k);
    	stCactusEdgeEnd *edgeEnd2 = stList_get(telomeres, k+1);

    	if(edgeEnd1 != edgeEnd2) { // Is a chain
    		stList *chain = stList_get(snarls->topLevelChains, i++);

    		// Check chain, recursively
    		checkSnarlChain(testCase, chain, 0);

			// Check boundaries are what we expect
			CuAssertTrue(testCase, edgeEnd1 == ((stSnarl *)stList_get(chain, 0))->edgeEnd1);
			CuAssertTrue(testCase, edgeEnd2 == ((stSnarl *)stList_peek(chain))->edgeEnd2);
    	}
    	else { // is a unary snarl
    		stSnarl *uSnarl = stList_get(snarls->topLevelUnarySnarls, j++);

    		// Check unary snarl, recursively
    		checkUnarySnarl(testCase, uSnarl);

    		// Check boundaries are what we expect
    		CuAssertTrue(testCase, edgeEnd1 == uSnarl->edgeEnd1);
    		CuAssertTrue(testCase, edgeEnd1 == uSnarl->edgeEnd2);
    	}
    }
}

static void getReachableBridges2(stCactusEdgeEnd *edgeEnd1,
		stHash *bridgeEndsToBridgeNodes, stList *bridgeEnds) {
	assert(edgeEnd1->link == NULL); // is a bridge

	// The node in the bridge graph incident with edgeEnd1
	stBridgeNode *bNode = stHash_search(bridgeEndsToBridgeNodes, edgeEnd1);

	// Walk from bNode to all the reachable nodes
	stSetIterator *endIt = stSet_getIterator(bNode->bridgeEnds);
	stCactusEdgeEnd *edgeEnd2;
	while((edgeEnd2 = stSet_getNext(endIt)) != NULL) {
		if(edgeEnd2 != edgeEnd1) {
			stList_append(bridgeEnds, edgeEnd2);
			getReachableBridges2(edgeEnd2->otherEdgeEnd, bridgeEndsToBridgeNodes, bridgeEnds);
		}
	}
	stSet_destructIterator(endIt);
}

static void getReachableBridges(stCactusEdgeEnd *edgeEnd1, stList *bridgeEnds) {
	/*
	 * Get the bridge ends that form boundary pairs with edgeEnd1.
	 */

	// Get bridge graph and map of bridge ends to bridge nodes in the bridge graph
	stBridgeGraph *bGraph = stBridgeGraph_getBridgeGraph(edgeEnd1->node);
	stHash *bridgeEndsToBridgeNodes = stBridgeGraph_getBridgeEdgeEndsToBridgeNodesHash(bGraph);

	// Do DFS to get reachable bridges
	getReachableBridges2(edgeEnd1, bridgeEndsToBridgeNodes, bridgeEnds);

	// Cleanup
	stHash_destruct(bridgeEndsToBridgeNodes);
	stBridgeGraph_destruct(bGraph);
}

static void addRandomTelomerePair(struct RandomCactusGraph *rGraph, stList *telomeres) {
	/*
	 * Finds a random pair of telomeres, which are are either a pair or bridge edge ends or a pair chain edge ends, oriented such that they
	 * form a pair of boundaries.
	 */

	// If empty graph, print warning and exit
	if(stSortedSet_size(rGraph->edgeEnds) == 0) {
		st_logCritical("Empty graph, no telomeres to select\n");
		return;
	}

	// Pick a random edge end
	stList *edgeEndsList = stSortedSet_getList(rGraph->edgeEnds);
	stCactusEdgeEnd *edgeEnd1 = st_randomChoice(edgeEndsList);
	stList_destruct(edgeEndsList);

	// Now find a compatible end
	stCactusEdgeEnd *edgeEnd2;

	// If a chain end
	if(edgeEnd1->link != NULL) {
		// Get the other elligible edge ends in the chain that form a pair of boundaries
		stList *boundaries = stList_construct();
		edgeEnd2 = edgeEnd1->link;
		do {
			stList_append(boundaries, edgeEnd2);
			edgeEnd2 = edgeEnd2->otherEdgeEnd->link;
		} while(!stList_contains(boundaries, edgeEnd2));
		edgeEnd2 = st_randomChoice(boundaries);
		stList_destruct(boundaries);
	}
	// Else, is a bridge end
	else {
		// Else, get the other bridges in the subtree
		stList *bridgeEnds = stList_construct();
		getReachableBridges(edgeEnd1, bridgeEnds);
		stList_append(bridgeEnds, edgeEnd1); // Case it is a unary top-level snarl

		// Pick a random one as the partner
		edgeEnd2 = st_randomChoice(bridgeEnds);

		// Cleanup
		stList_destruct(bridgeEnds);
	}

	// Add to telomeres
	stList_append(telomeres, edgeEnd1);
	stList_append(telomeres, edgeEnd2);
}

static void testStCactusGraph_tinySnarlTest(CuTest *testCase) {
    // Define a graph of two sequences connected back-to-back
    
    // The graph
    stCactusGraph* cactusGraph = stCactusGraph_construct();

    // External containers for tracking nodes and edges
    stList* nodeObjects = stList_construct3(0, free);
    stSortedSet* edgeEnds = stSortedSet_construct();

    // Create the nodes (3 of them)
    for (int64_t i = 0; i < 3; i++) {
        int64_t *j = st_malloc(sizeof(int64_t));
        j[0] = i;
        stCactusNode_construct(cactusGraph, j);
        stList_append(nodeObjects, j);
    }

    // Connect node 0 to node 1
    void *nodeObject1 = stList_get(nodeObjects, 0);
    void *nodeObject2 = stList_get(nodeObjects, 1);
    stCactusNode *node1 = stCactusGraph_getNode(cactusGraph, nodeObject1);
    assert(node1 != NULL);
    stCactusNode *node2 = stCactusGraph_getNode(cactusGraph, nodeObject2);
    assert(node2 != NULL);
    stCactusEdgeEnd *edgeEnd = stCactusEdgeEnd_construct(cactusGraph, node1, node2, nodeObject1, nodeObject2);
    stSortedSet_insert(edgeEnds, edgeEnd);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd));

    // The right side of this edge is one telomere
    stCactusEdgeEnd* telomere1 = stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd);
    
    // Connect node 2 to node 1
    nodeObject1 = stList_get(nodeObjects, 2);
    nodeObject2 = stList_get(nodeObjects, 1);
    node1 = stCactusGraph_getNode(cactusGraph, nodeObject1);
    assert(node1 != NULL);
    node2 = stCactusGraph_getNode(cactusGraph, nodeObject2);
    assert(node2 != NULL);
    edgeEnd = stCactusEdgeEnd_construct(cactusGraph, node1, node2, nodeObject1, nodeObject2);
    stSortedSet_insert(edgeEnds, edgeEnd);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd));
    
    // The right side of this edge is the other telomere
    stCactusEdgeEnd* telomere2 = stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd);

    // Collapse to cactus
    stCactusGraph_collapseToCactus(cactusGraph, mergeNodeObjects, stList_get(nodeObjects, 0));
    
    // Add the two inside edge ends as telomeres
    stList *telomeres = stList_construct();
    stList_append(telomeres, (void*) telomere1);
    stList_append(telomeres, (void*) telomere2);

    // Make snarls
    stSnarlDecomposition *snarls = stCactusGraph_getSnarlDecomposition(cactusGraph, telomeres);
    
    // Make sure we got the right number
    CuAssertIntEquals(testCase, stList_length(telomeres)/2,
        stList_length(snarls->topLevelChains) + stList_length(snarls->topLevelUnarySnarls));
    
    // Clean up the snarls
    stSnarlDecomposition_destruct(snarls);
    
    // And up the telomeres
    stList_destruct(telomeres);
    
    // And the cactus graph
    stCactusGraph_destruct(cactusGraph);
    
    // And the node objects in their list
    stList_destruct(nodeObjects);
    
    // And the edge ends
    stSortedSet_destruct(edgeEnds);
        
}

static void testStCactusGraph_unreachableSnarlTest(CuTest *testCase) {
    /* 
     * Define a graph with two tips that can't reach each other.
     *
     *    1\
     *  2---3
     *  v\4 v
     *
     * The head is 1, the tail is 4, 2 and 3 have self loops, and the graph is
     * connected. But the head cannot reach the tail.
     */

    
    // The graph
    stCactusGraph* cactusGraph = stCactusGraph_construct();

    // External containers for tracking nodes and edges
    stList* nodeObjects = stList_construct3(0, free);
    stSortedSet* edgeEnds = stSortedSet_construct();

    // Create the adjacency component nodes (5 of them)
    for (int64_t i = 0; i < 5; i++) {
        int64_t *j = st_malloc(sizeof(int64_t));
        j[0] = i;
        stCactusNode_construct(cactusGraph, j);
        stList_append(nodeObjects, j);
    }

    // Node 1 connects component 0 to component 1
    stCactusEdgeEnd *edgeEnd1 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 0)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stList_get(nodeObjects, 0),
        stList_get(nodeObjects, 1));
    stSortedSet_insert(edgeEnds, edgeEnd1);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd1));
    
    // Node 2 connects component 2 to component 1
    stCactusEdgeEnd *edgeEnd2 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 2)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stList_get(nodeObjects, 2),
        stList_get(nodeObjects, 1));
    stSortedSet_insert(edgeEnds, edgeEnd2);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd2));
    
    // Node 3 connects component 1 to component 3
    stCactusEdgeEnd *edgeEnd3 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 3)),
        stList_get(nodeObjects, 1),
        stList_get(nodeObjects, 3));
    stSortedSet_insert(edgeEnds, edgeEnd3);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd3));
    
    // Node 4 connects component 1 to component 4
    stCactusEdgeEnd *edgeEnd4 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 4)),
        stList_get(nodeObjects, 1),
        stList_get(nodeObjects, 4));
    stSortedSet_insert(edgeEnds, edgeEnd4);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd4));

    // The right side of node 1's edge is one telomere
    stCactusEdgeEnd* telomere1 = stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd1);
    
    // The left side of node 4's edge is the other telomere
    stCactusEdgeEnd* telomere2 = edgeEnd4;

    // Collapse to cactus
    stCactusGraph_collapseToCactus(cactusGraph, mergeNodeObjects, stList_get(nodeObjects, 0));
    
    // Add the two inside edge ends as telomeres
    stList *telomeres = stList_construct();
    stList_append(telomeres, (void*) telomere1);
    stList_append(telomeres, (void*) telomere2);

    // Make snarls
    stSnarlDecomposition *snarls = stCactusGraph_getSnarlDecomposition(cactusGraph, telomeres);
    
    // Make sure we got the right number of items (one chain per telomere pair)
    CuAssertIntEquals(testCase, stList_length(telomeres)/2,
        stList_length(snarls->topLevelChains) + stList_length(snarls->topLevelUnarySnarls));
        
    // Make sure it really is a chain and not a unary snarl.
    CuAssertIntEquals(testCase, 1, stList_length(snarls->topLevelChains));
    
    // Make sure it has one top-level snarl
    stList* chain1 = stList_get(snarls->topLevelChains, 0);
    CuAssertIntEquals(testCase, 1, stList_length(chain1));
    stSnarl* snarl = stList_get(chain1, 0);
    
    // Make sure that snarl has 2 unary children (one per graph sequence node)
    CuAssertIntEquals(testCase, 0, stList_length(snarl->chains));
    CuAssertIntEquals(testCase, 2, stList_length(snarl->unarySnarls));
    
    // Clean up the snarls
    stSnarlDecomposition_destruct(snarls);
    
    // And up the telomeres
    stList_destruct(telomeres);
    
    // And the cactus graph
    stCactusGraph_destruct(cactusGraph);
    
    // And the node objects in their list
    stList_destruct(nodeObjects);
    
    // And the edge ends
    stSortedSet_destruct(edgeEnds);
        
}

static void testStCactusGraph_adjacentSnarlTest(CuTest *testCase) {
    /* 
     * Define a graph with two adjacent bubbles
     *
     *   2   5
     * 1   4   7
     *   3   6
     *
     * We need to make sure the bubbles don't contain unary child snarls that want to contain the other bubbles.
     */

    
    // The graph
    stCactusGraph* cactusGraph = stCactusGraph_construct();

    // External containers for tracking nodes and edges
    stList* nodeObjects = stList_construct3(0, free);
    stSortedSet* edgeEnds = stSortedSet_construct();

    // Create the adjacency component nodes (6 of them)
    for (int64_t i = 0; i < 6; i++) {
        int64_t *j = st_malloc(sizeof(int64_t));
        j[0] = i;
        stCactusNode_construct(cactusGraph, j);
        stList_append(nodeObjects, j);
    }

    // Node 1 connects component 0 to component 1
    stCactusEdgeEnd *edgeEnd1 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 0)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stList_get(nodeObjects, 0),
        stList_get(nodeObjects, 1));
    stSortedSet_insert(edgeEnds, edgeEnd1);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd1));
    
    // Node 2 connects component 1 to component 2
    stCactusEdgeEnd *edgeEnd2 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 2)),
        stList_get(nodeObjects, 1),
        stList_get(nodeObjects, 2));
    stSortedSet_insert(edgeEnds, edgeEnd2);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd2));
    
    // Node 3 connects component 1 to component 2
    stCactusEdgeEnd *edgeEnd3 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 1)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 2)),
        stList_get(nodeObjects, 1),
        stList_get(nodeObjects, 2));
    stSortedSet_insert(edgeEnds, edgeEnd3);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd3));
    
    // Node 4 connects component 2 to component 3
    stCactusEdgeEnd *edgeEnd4 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 2)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 3)),
        stList_get(nodeObjects, 2),
        stList_get(nodeObjects, 3));
    stSortedSet_insert(edgeEnds, edgeEnd4);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd4));
    
    // Node 5 connects component 3 to component 4
    stCactusEdgeEnd *edgeEnd5 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 3)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 4)),
        stList_get(nodeObjects, 3),
        stList_get(nodeObjects, 4));
    stSortedSet_insert(edgeEnds, edgeEnd5);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd5));
    
    // Node 6 connects component 3 to component 4
    stCactusEdgeEnd *edgeEnd6 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 3)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 4)),
        stList_get(nodeObjects, 3),
        stList_get(nodeObjects, 4));
    stSortedSet_insert(edgeEnds, edgeEnd6);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd6));
    
    // Node 7 connects component 4 to component 5
    stCactusEdgeEnd *edgeEnd7 = stCactusEdgeEnd_construct(cactusGraph,
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 4)),
        stCactusGraph_getNode(cactusGraph, stList_get(nodeObjects, 5)),
        stList_get(nodeObjects, 4),
        stList_get(nodeObjects, 5));
    stSortedSet_insert(edgeEnds, edgeEnd7);
    stSortedSet_insert(edgeEnds, stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd7));

    // The right side of node 1's edge is one telomere
    stCactusEdgeEnd* telomere1 = stCactusEdgeEnd_getOtherEdgeEnd(edgeEnd1);
    
    // The left side of node 7's edge is the other telomere
    stCactusEdgeEnd* telomere2 = edgeEnd7;

    // Collapse to cactus
    stCactusGraph_collapseToCactus(cactusGraph, mergeNodeObjects, stList_get(nodeObjects, 0));
    
    // Add the two inside edge ends as telomeres
    stList *telomeres = stList_construct();
    stList_append(telomeres, (void*) telomere1);
    stList_append(telomeres, (void*) telomere2);
    CuAssertTrue(testCase, telomere1->link == NULL);
    CuAssertTrue(testCase, telomere2->link == NULL);

    // Make snarls
    stSnarlDecomposition *snarls = stCactusGraph_getSnarlDecomposition(cactusGraph, telomeres);

    // Make sure we got the right number of items (one chain per telomere pair)
    CuAssertIntEquals(testCase, stList_length(telomeres)/2,
        stList_length(snarls->topLevelChains) + stList_length(snarls->topLevelUnarySnarls));
        
    // Make sure it really is a chain and not a unary snarl.
    CuAssertIntEquals(testCase, 1, stList_length(snarls->topLevelChains));
    
    // Make sure it has two top-level snarls
    stList* chain1 = stList_get(snarls->topLevelChains, 0);
    CuAssertIntEquals(testCase, 2, stList_length(chain1));
    stSnarl* snarl1 = stList_get(chain1, 0);
    stSnarl* snarl2 = stList_get(chain1, 1);
    
    // Make sure that snarl1 has 0 chains and 0 unary children
    CuAssertIntEquals(testCase, 0, stList_length(snarl1->chains));
    CuAssertIntEquals(testCase, 0, stList_length(snarl1->unarySnarls));
    
    // Make sure that snarl2 has 0 chains and 0 unary children
    CuAssertIntEquals(testCase, 0, stList_length(snarl2->chains));
    CuAssertIntEquals(testCase, 0, stList_length(snarl2->unarySnarls));
    
    // Clean up the snarls
    stSnarlDecomposition_destruct(snarls);
    
    // And up the telomeres
    stList_destruct(telomeres);
    
    // And the cactus graph
    stCactusGraph_destruct(cactusGraph);
    
    // And the node objects in their list
    stList_destruct(nodeObjects);
    
    // And the edge ends
    stSortedSet_destruct(edgeEnds);
        
}


static void testStCactusGraph_randomSnarlTest(CuTest *testCase) {
    // Creates problem instances, then checks resulting snarl set.
    for (int64_t test = 0; test < 1000; test++) {
        // Make a random graph
        struct RandomCactusGraph *rGraph = getRandomCactusGraph(0);

        // Get a random set of one or more telomere pairs
        stList *telomeres = stList_construct();
        do {
        	addRandomTelomerePair(rGraph, telomeres);
        } while(st_random() > 0.5);

        // Make snarls
        stSnarlDecomposition *snarls = stCactusGraph_getSnarlDecomposition(rGraph->cactusGraph, telomeres);

        // Print the bridge graphs
        /*stList *components = stCactusGraph_getComponents(rGraph->cactusGraph, 0);
        for(int64_t i=0; i<stList_length(components); i++) {
            stSet *component = stList_get(components, i);
            stBridgeGraph *bridgeGraph = stBridgeGraph_getBridgeGraph(stSet_peek(component));
            for(int64_t j=0; j<stList_length(bridgeGraph->bridgeNodes); j++) {
                stBridgeNode_print(stList_get(bridgeGraph->bridgeNodes, j), stdout);
            }
            stBridgeGraph_destruct(bridgeGraph);
        }
        stList_destruct(components);*/

        // Print the snarl decomposition
        //stSnarlDecomposition_print(snarls, stdout);

        // Test the snarls
        checkSnarlDecomposition(testCase, snarls, telomeres);

        // Cleanup
        destroyRandomCactusGraph(rGraph);
        stSnarlDecomposition_destruct(snarls);
        stList_destruct(telomeres);
    }
}

CuSuite* stCactusGraphsTestSuite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testStCactusNode);
    SUITE_ADD_TEST(suite, testStCactusEdgeEnd);
    SUITE_ADD_TEST(suite, testStCactusGraph);
    SUITE_ADD_TEST(suite, testStCactusGraph_unmarkAndMarkCycles);
    SUITE_ADD_TEST(suite, testStCactusGraph_collapseBridges);
    SUITE_ADD_TEST(suite, testStCactusGraph_breakChainsByEndsNotInChains);
    SUITE_ADD_TEST(suite, testStCactusGraph_randomTest);
    SUITE_ADD_TEST(suite, testStCactusGraph_getComponents);
    SUITE_ADD_TEST(suite, testStCactusGraph_getBridgeGraphs);
    SUITE_ADD_TEST(suite, testStCactusGraph_tinySnarlTest);
    SUITE_ADD_TEST(suite, testStCactusGraph_unreachableSnarlTest);
    SUITE_ADD_TEST(suite, testStCactusGraph_adjacentSnarlTest);
    SUITE_ADD_TEST(suite, testStCactusGraph_randomSnarlTest);
    return suite;
}
