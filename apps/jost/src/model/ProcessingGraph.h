/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_JOSTPROCESSINGGRAPH_HEADER__
#define __JUCETICE_JOSTPROCESSINGGRAPH_HEADER__

#include "BasePlugin.h"


class ProcessingNode;


//==============================================================================
/**
        A single connection between 2 nodes
*/
class ProcessingLink
{
public:
    int sourcePort;
    ProcessingNode* destination;
    int destinationPort;
};


//==============================================================================
/**
        A single node of a graph having multiple links

*/
class ProcessingNode
{
public:

    //==============================================================================
    /** Constructor */
    ProcessingNode (void* data_)
        : data (data_)
    {
    }

    /** Destructor */
    ~ProcessingNode ()
    {
        deleteAllLinks ();
    }

    //==============================================================================
    /** Connect an output port of this node with an input of another one

        No checks are made to do this connection, so you should be sure that the
        destination pointer exists, and src/dest ports have a correct index.
    */
    void connectTo (const int sourcePort,
                    ProcessingNode* destination,
                    const int destinationPort,
                    const int type)
    {
        ProcessingLink* link = new ProcessingLink ();

        link->sourcePort = sourcePort;
        link->destination = destination;
        link->destinationPort = destinationPort;

        links[type].add (link);
    }

    //==============================================================================
    /** Returns the number of connections available */
    inline int getLinksCount (const int type) const     { return links[type].size (); }

    /** Return a plugin connection */
    inline ProcessingLink* getLink (const int type, const int index) const
    {
        return (ProcessingLink*) links[type].getUnchecked (index);
    }

    /** Clears all available connections, freeing up */
    inline void deleteAllLinks (const int type = -1)
    {
        if (type == 0 || type < 0) {
            for (int i = links[0].size (); --i >= 0;)
                delete ((ProcessingLink*) links[0].getUnchecked (i));
            links[0].clear ();
        }

        if (type == 1 || type < 0) {
            for (int i = links[1].size (); --i >= 0;)
                delete ((ProcessingLink*) links[1].getUnchecked (i));
            links[1].clear ();
        }
    }

    //==============================================================================
    /** Returns the number of connections available */
    inline void* getData () const                 { return data; }

    /** Returns the number of connections available */
    inline void setData (void* data_)             { data = data_; }

private:

    friend class ProcessingGraph;

    void* data;
    VoidArray links[2];
};



//==============================================================================
/**
        A graph which holds a set of nodes connected togheter

*/
class ProcessingGraph
{
public:

    //==============================================================================
    ProcessingGraph ()
    {
    }

    ~ProcessingGraph ()
    {
        deleteAllNodes ();
    }

    //==============================================================================
    ProcessingNode* addNode (void* data)
    {
        ProcessingNode* node = new ProcessingNode (data);

        nodes.add (node);

        return node;
    }

    ProcessingNode* insertNode (const int index, void* data)
    {
        ProcessingNode* node = new ProcessingNode (data);

        nodes.insert (index, node);

        return node;
    }

    void removeNode (void* data)
    {
        for (int i = nodes.size (); --i >= 0;)
        {
            ProcessingNode* node = (ProcessingNode*) nodes.getUnchecked (i);
            if (node->data == data)
            {
                nodes.removeValue (node);
                delete node;
            }
        }
    }

    //==============================================================================
    /** Connect 2 nodes togheter

    */
    void connectTo (void* source,
                    const int sourcePort,
                    void* destination,
                    const int destinationPort,
                    const int type)
    {
        ProcessingNode* sourceNode = 0;
        ProcessingNode* destinationNode = 0;
        for (int i = nodes.size (); --i >= 0;)
        {
            ProcessingNode* node = (ProcessingNode*) nodes.getUnchecked (i);

            if (node->data == source) sourceNode = node;
            if (node->data == destination) destinationNode = node;
        }

        if (sourceNode == 0)
        {
            sourceNode = addNode (source);
        }

        if (destinationNode == 0)
            destinationNode = addNode (destination);

        sourceNode->connectTo (sourcePort,
                               destinationNode,
                               destinationPort,
                               type);
    }

    //==============================================================================
    int getNodeCount () const                 { return nodes.size (); }

    ProcessingNode* getNode (const int index) const
    {
        return (ProcessingNode*) nodes.getUnchecked (index);
    }

    void* getData (const int index) const
    {
        return ((ProcessingNode*) nodes.getUnchecked (index))->data;
    }

    //==============================================================================
    void deleteAllNodes ()
    {
        for (int i = nodes.size (); --i >= 0;)
            delete ((ProcessingNode*) nodes.getUnchecked (i));

        nodes.clear ();
    }

    //==============================================================================
    bool contains (void* data)
    {
        for (int i = nodes.size (); --i >= 0;)
            if (((ProcessingNode*) nodes.getUnchecked (i))->data == data)
                return true;

        return false;
    }

    ProcessingNode* findNode (void* data)
    {
        for (int i = nodes.size (); --i >= 0;) {
            ProcessingNode* node = (ProcessingNode*) nodes.getUnchecked (i);
            if (node->data == data)
                return node;
        }

        return false;
    }

    //==============================================================================
    void resetNodeData (void* data)
    {
        for (int i = nodes.size (); --i >= 0;)
        {
            ProcessingNode* node = (ProcessingNode*) nodes.getUnchecked (i);
            if (node->data == data)
            {
                node->setData (0);
                break;
            }
        }
    }


private:

    VoidArray nodes;
};



#endif
