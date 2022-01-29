#include "../../inc/client.h"

void join_chat_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    char *chat_name = (char *)gtk_widget_get_name(widget);

    if (event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        set_chatlist_item_active(widget);
    }
    else if (event->type == GDK_DOUBLE_BUTTON_PRESS && event->button == 1)
    {
        int response_code = handle_join_chat_request(chat_name);
        handle_join_chat_response_code(response_code, chat_name);
        
        GtkWidget *search_field = get_widget_by_name_r(main_window, "global_search_field");
        gtk_entry_set_text(GTK_ENTRY(search_field), "");
    }
}

void add_join_chat_item(int id, char *chat_name)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");

    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(chatlist_container), event_box, FALSE, FALSE, 0);
    // gtk_widget_set_name(event_box, mx_itoa(id));
    gtk_widget_set_name(event_box, chat_name);
    add_class(event_box, "chatlist_item_wrap");
	g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(join_chat_event), NULL);

    GtkWidget *chatlist_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(chatlist_item, mx_itoa(id));
    add_class(chatlist_item, "chatlist_item");
    gtk_container_add(GTK_CONTAINER(event_box), chatlist_item);

    GtkWidget *chatlist_item_id = gtk_label_new(mx_itoa(id)); ///CHAT ID
    gtk_widget_set_name(chatlist_item_id, "chat_id");
    add_class(chatlist_item_id, "hidden");
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_id, FALSE, FALSE, 0);

    // GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *avatar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    // g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)list->avatar);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    add_class(avatar, "chatlist_item_avatar");
    gtk_box_pack_start(GTK_BOX(chatlist_item), avatar, FALSE, FALSE, 0);

    // text block
    GtkWidget *chatlist_item_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_text, false, false, 0);
    add_class(chatlist_item_text, "chatlist_item_text");

    GtkWidget *chatlist_item_title = gtk_label_new(chat_name);
    // gtk_widget_set_name(chatlist_item_title, "chat_name");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_title, false, false, 0);
    // GtkWidget *chat_list_item_message = gtk_label_new("Last message");
    // gtk_widget_set_halign(GTK_WIDGET(chat_list_item_message), GTK_ALIGN_START);
    // gtk_box_pack_start(GTK_BOX(chatlist_item_text), chat_list_item_message, false, false, 0);
    //

    // info block
    // GtkWidget *chatlist_item_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_halign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    // // gtk_widget_set_valign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    // gtk_box_pack_end(GTK_BOX(chatlist_item), chatlist_item_info, false, false, 0);
    // add_class(chatlist_item_info, "chatlist_item_info");

    // GtkWidget *chatlist_item_time = gtk_label_new("15:00");
    // gtk_widget_set_valign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_START);
    // gtk_widget_set_halign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_END);
    // gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_time, false, false, 0);
    // add_class(chatlist_item_time, "chatlist_item_time");
    // GtkWidget *chatlist_item_notify = gtk_label_new("2");
    // gtk_widget_set_size_request(GTK_WIDGET(chatlist_item_notify), 20, 20);
    // gtk_widget_set_valign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    // gtk_widget_set_halign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    // gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_notify, false, false, 0);
    // add_class(chatlist_item_notify, "chatlist_item_notify");
    //

    gtk_widget_show_all(event_box);
}