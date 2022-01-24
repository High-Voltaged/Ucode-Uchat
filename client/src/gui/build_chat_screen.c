#include "../../inc/client.h"

void build_leftbar(GtkWidget *chat_screen)
{
    GtkWidget *left_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(left_bar), LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), left_bar, 0, 0, 1, 1);
    add_class(left_bar, "left_bar");

    // search block
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    // gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
    add_class(left_bar, "search_block");

    GtkWidget *search_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search");
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    //

    // chat list
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    add_class(scrollable_wrap, "scrollable_wrap");
    // gtk_widget_set_size_request(scrollable_wrap, LEFT_BAR_W, LEFT_BAR_H - 104);
    GtkWidget *chat_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    t_chat_screen.chat_list = chat_list;
    add_class(chat_list, "chat_list");
    // gtk_widget_set_size_request(chat_list, LEFT_BAR_W, LEFT_BAR_H - 104);
    gtk_widget_set_tooltip_text(chat_list, "chat_list");
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_list);
    // gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scrollable_wrap)));
    //

    GtkWidget *create_new_chat_btn = gtk_event_box_new();
    add_class(create_new_chat_btn, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(create_new_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "button_press_event", G_CALLBACK(popup_create_chat_menu), chat_screen);
    GtkWidget *signup_label = gtk_label_new("Create new group");
    add_class(signup_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(create_new_chat_btn), signup_label);

    gtk_box_pack_start(GTK_BOX(left_bar), search_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), create_new_chat_btn, FALSE, FALSE, 0);
}

void build_rightbar(GtkWidget *chat_screen)
{
    GtkWidget *chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(chat, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(chat), WINDOW_WIDTH - LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), chat, 1, 0, 2, 1);
    add_class(chat, "chat");

    GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat), messaging_label, FALSE, FALSE, 0);
    gtk_widget_set_vexpand(messaging_label, TRUE);
    gtk_widget_set_hexpand(messaging_label, TRUE);
}

void build_chat_screen(GtkWidget **main_area)
{
    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);
    gtk_container_add(GTK_CONTAINER(*main_area), grid);


    build_leftbar(grid);
    build_rightbar(grid);

    gtk_widget_show_all(grid);
}