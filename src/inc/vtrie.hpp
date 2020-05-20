#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <stack>

#include "node.hpp"
#include "path.hpp"
#include "db.hpp"
#include "batchdbop.hpp"

class VTrie {
    private:
        buffer_t EMPTY_TRIE_ROOT_;
        buffer_t root_;
        DBConnection db_;
        // Todo Add Semaphore for locking the resource under processing

        Node LookupNode(const bufferarray_t &node);
        void PutNode(const Node &node);
        void FindValueNodes(); // Todo need to check what should be passed as parameter
        void FindDbNodes(); // Todo need to check what should be passed as parameter
        void UpdateNode(const buffer_t &key, const buffer_t &value, const nibble_t &key_reminder, const Node stack[]);
        void WalkTree(const buffer_t &root); // Todo need to check what should be passed as parameter
        void SaveStack(const nibble_t &key, const std::stack<Node> &stack, const batchdboparray_t &op_stack);
        void DeleteNode(const buffer_t &key, const Node stack[]);
        void CreateInitilNode(const buffer_t &key, const buffer_t &value);
        bufferarray_t FormatNode(const Node &node, const bool top_level, const batchdboparray_t &op_stack, const bool remove=false);

    public:
        // VTrie();
        // ~VTrie();

        VTrie(DBConnection &db, const buffer_t &root);
        buffer_t GetRoot();
        void Root(const buffer_t &root);
        void SetRoot(const buffer_t &root);

        VTrie FromProof(const bufferarray_t &proof_nodes, const VTrie &proof_trie);
        bufferarray_t Prove(const VTrie &trie, const buffer_t &key);
        buffer_t VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes);

        Path FindPath(const buffer_t &key);
        VTrie Copy();
        void Batch(const batchdboparray_t &op_stack);
        bool CheckRoot(const buffer_t &root);
        
        buffer_t Select(const buffer_t &key);
        buffer_t Select(const buffer_t &root_hash, const buffer_t &key);
        bool Insert(const buffer_t &key, const buffer_t &value);
        bool Delet(const buffer_t &key);
        bool Update(const buffer_t &key, const buffer_t &value);
};

#endif