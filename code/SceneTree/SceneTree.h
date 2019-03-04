#ifndef __SCENE_TREE_H__
#define __SCENE_TREE_H__

#include <SDL2/SDL.h>
#include <vector>
#include "../BaseClass/SceneBase.h"
#include <string>

using std::vector;
using std::string;

typedef struct CSceneTreeNode
{
    CSceneTreeNode* mParent;
    string mSceneName;
    CSceneBase* mScene;
    vector<CSceneTreeNode*> mChildNode;
}CSceneTreeNode;

class CSceneTree
{
    private:
    CSceneTreeNode* mRoot;
    CSceneTreeNode* mCurrentNode;

    public:
    CSceneTreeNode* searchTreeNode(string sceneName);
    CSceneTree();
    ~CSceneTree();

    void addChild(string sceneName, CSceneTreeNode* child);
    void setRootScene(string rootScenePath);
    CSceneBase* getCurrentScene();
    bool back();
    bool enter(string sceneName);
    bool loadMedia(SDL_Renderer* renderer);
};


#endif