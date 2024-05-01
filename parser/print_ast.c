/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:44:13 by jle-goff          #+#    #+#             */
/*   Updated: 2024/05/01 16:03:06 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

// void print_node_type(int type)
// {
//     switch (type) {
//         case WORD:
//             printf("WORD");
//             break;
//         case PIPE:
//             printf("PIPE");
//             break;
//         case REDIR_APP:
//             printf("REDIR_APP");
// 			break;
// 		case REDIR_DELIMIT:
//             printf("REDIR_DELIMIT");
// 			break;
// 		case REDIR_IN:
//             printf("REDIR_IN");
// 			break;
// 		case REDIR_OUT:
//             printf("REDIR_OUT");
//             break;
//         default:
//             printf("NULL");
//     }
// }

// void print_tree_helper(t_ast *node, int level) 
// {
// 	for (int i = 0; i < level; i++) {

// 	printf("    ");
// 	}
// 		if (node == NULL) {
// 			printf("null node\n");
// 			return ;
// 	}
// 	printf("Type: ");
// 	print_node_type(node->type);
// 	printf(", Value: %s\n", node->value);
// 	print_tree_helper(node->left, level + 1);
// 	print_tree_helper(node->right, level + 1);
// }

// void print_tree(t_ast *root)
// {
// 	printf("Root\n");
// 	print_tree_helper(root, 1);
// } 