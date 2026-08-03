/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:12:14 by capapes           #+#    #+#             */
/*   Updated: 2025/12/05 13:29:48 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


document.addEventListener("DOMContentLoaded", () => {
    const themeSelect = document.getElementById("themeSelect");

    if (!themeSelect) return;

    // Apply initial theme (default = light)
    document.documentElement.setAttribute("data-theme", "light");

    // Change theme immediately on selection
    themeSelect.addEventListener("change", (e) => {
        const selected = e.target.value;
        document.documentElement.setAttribute("data-theme", selected);
    });
});