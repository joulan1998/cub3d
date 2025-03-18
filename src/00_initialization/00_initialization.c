#include "../../headers/cub3d.h"

/**
 * @brief Initializes the parameters of the t_params structure.
 *
 * This function sets the initial values for the t_params structure fields.
 * It sets all texture pointers to NULL, floor and ceiling colors to -1,
 * and map dimensions to -1.
 *
 * @param params Pointer to the t_params structure to be initialized.
 */
void	init_params(t_params *params)
{
	params->map = NULL;
	params->no_texture = NULL;
	params->so_texture = NULL;
	params->we_texture = NULL;
	params->ea_texture = NULL;
	params->floor_color = -1;
	params->ceiling_color = -1;
	params->map_width = 0;
	params->map_height = 0;
}
