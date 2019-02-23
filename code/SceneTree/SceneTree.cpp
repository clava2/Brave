#include "SceneTree.h"
#include <stack>
#include <iostream>
#include <yaml-cpp/yaml.h>

using std::cout;
using std::endl;

using std::stack;

CSceneTree::CSceneTree()
{
    mCurrentNode = NULL;
    mRoot.mSceneName = "root";
}

CSceneTree::~CSceneTree()
{
}

CSceneTreeNode* CSceneTree::searchTreeNode(string sceneName)
{
    stack<CSceneTreeNode*> nodeStack;
    nodeStack.push(&mRoot);
    CSceneTreeNode* tempNode = NULL;
    while(!nodeStack.empty())
    {
        tempNode = nodeStack.top();
        nodeStack.pop();
        if(tempNode->mSceneName == sceneName)
        {
            return tempNode;
        }
        for(CSceneTreeNode* childNode: tempNode->mChildNode)
        {
            nodeStack.push(childNode);
        }
    }
    return NULL;
}

void CSceneTree::addChild(string sceneName, CSceneTreeNode* child)
{
    CSceneTreeNode* tempNode = searchTreeNode(sceneName);
    tempNode->mChildNode.push_back(child);
}

CSceneBase* CSceneTree::getCurrentScene()
{
    return mCurrentNode->mScene;
}

bool CSceneTree::back()
{
    mCurrentNode = mCurrentNode->mParent;
    return mCurrentNode == NULL;
}

bool CSceneTree::enter(string sceneName)
{
    for(CSceneTreeNode* tempScene : mCurrentNode->mChildNode)
    {
        if(tempScene->mSceneName == sceneName)
        {
            mCurrentNode = tempScene;
            return true;
        }
    }
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Can not find Scene: %s",sceneName.c_str());
    return false;
}