#include "TreeTraversal.h"
#include <iostream>
#include <string>

// Exemple d'utilisation de la classe TreeTraversal
void demonstrateTreeTraversal()
{
    // Créer un arbre d'exemple avec des noms de personnages
    auto root = std::make_unique<TreeNode<std::string>>("Héros");
    
    // Ajouter des enfants
    auto* warrior = root->addChild("Guerrier");
    auto* mage = root->addChild("Mage");
    auto* archer = root->addChild("Archer");
    
    // Ajouter des sous-classes
    warrior->addChild("Paladin");
    warrior->addChild("Berserker");
    
    mage->addChild("Élémentaire");
    mage->addChild("Nécromancien");
    auto* illusionist = mage->addChild("Illusionniste");
    
    archer->addChild("Ranger");
    archer->addChild("Assassin");
    
    // Ajouter des spécialisations
    illusionist->addChild("Maître des illusions");
    illusionist->addChild("Contrôleur mental");
    
    // Créer le parcours
    TreeTraversal<std::string> traversal(root.get());
    
    std::cout << "=== Démonstration du parcours d'arbre ===\n\n";
    
    // Parcours préfixe
    std::cout << "Parcours préfixe (racine, enfants):\n";
    traversal.traverse(TreeTraversal<std::string>::TraversalType::PREORDER, 
        [](const std::string& data) {
            std::cout << "- " << data << "\n";
        });
    
    std::cout << "\nParcours suffixe (enfants, racine):\n";
    traversal.traverse(TreeTraversal<std::string>::TraversalType::POSTORDER, 
        [](const std::string& data) {
            std::cout << "- " << data << "\n";
        });
    
    std::cout << "\nParcours par niveau:\n";
    traversal.traverse(TreeTraversal<std::string>::TraversalType::LEVEL_ORDER, 
        [](const std::string& data) {
            std::cout << "- " << data << "\n";
        });
    
    std::cout << "\nParcours par niveau avec profondeur:\n";
    traversal.traverseByLevel([](const std::string& data, size_t level) {
        for (size_t i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        std::cout << "Niveau " << level << ": " << data << "\n";
    });
    
    // Recherche de nœuds
    std::cout << "\nRecherche de nœuds contenant 'Mage':\n";
    auto mageNodes = traversal.findNodes([](const std::string& data) {
        return data.find("Mage") != std::string::npos;
    });
    
    for (const auto& node : mageNodes) {
        std::cout << "- " << node << "\n";
    }
    
    // Recherche d'un nœud spécifique
    std::cout << "\nRecherche du nœud 'Illusionniste':\n";
    auto* foundNode = traversal.findNode("Illusionniste");
    if (foundNode) {
        std::cout << "Nœud trouvé: " << foundNode->getData() << "\n";
        std::cout << "Profondeur: " << foundNode->getDepth() << "\n";
        std::cout << "Hauteur: " << foundNode->getHeight() << "\n";
        std::cout << "Nombre d'enfants: " << foundNode->getChildCount() << "\n";
    }
    
    // Statistiques de l'arbre
    std::cout << "\nStatistiques de l'arbre:\n";
    std::cout << "- Nombre total de nœuds: " << traversal.getNodeCount() << "\n";
    std::cout << "- Nombre de feuilles: " << traversal.getLeafCount() << "\n";
    std::cout << "- Profondeur maximale: " << traversal.getMaxDepth() << "\n";
    
    // Parcours avec prédicat complexe
    std::cout << "\nNœuds de niveau 2 (profondeur 2):\n";
    traversal.traverseByLevel([](const std::string& data, size_t level) {
        if (level == 2) {
            std::cout << "- " << data << "\n";
        }
    });
}

// Exemple d'utilisation avec des entiers
void demonstrateIntegerTree()
{
    std::cout << "\n\n=== Exemple avec des entiers ===\n\n";
    
    auto root = std::make_unique<TreeNode<int>>(10);
    
    auto* left = root->addChild(5);
    auto* right = root->addChild(15);
    
    left->addChild(3);
    left->addChild(7);
    
    right->addChild(12);
    right->addChild(20);
    
    TreeTraversal<int> traversal(root.get());
    
    std::cout << "Parcours préfixe des entiers:\n";
    auto preorder = traversal.getTraversal(TreeTraversal<int>::TraversalType::PREORDER);
    for (int value : preorder) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    std::cout << "Nombres pairs:\n";
    auto evenNumbers = traversal.findNodes([](int value) {
        return value % 2 == 0;
    });
    for (int value : evenNumbers) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}
