#include "../../inc/client.h"

void load_css()
{
	GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "client/data/styles/main.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void add_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, class_name);
}

void remove_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, class_name);
}

void on_crossing(GtkWidget *widget, GdkEventCrossing *event)
{
	GdkDisplay *display = gtk_widget_get_display(widget);
	GdkCursor *cursor = NULL;	

	switch (gdk_event_get_event_type((GdkEvent*)event))
	{
		case GDK_ENTER_NOTIFY:
			gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE); // it's for trigger :hover for this widget in CSS
			cursor = gdk_cursor_new_from_name (display, "hand1");
			break;

		case GDK_LEAVE_NOTIFY:
			gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
			cursor = gdk_cursor_new_from_name (display, "default");
			break;

		default:
			break;
	}

	gdk_window_set_cursor (gtk_widget_get_window(widget), cursor);

	// Release the reference on the cursor
	g_object_unref(cursor);
}

void set_field_error_style(GtkWidget *field)
{
    remove_class(field, "input-field--success");
    add_class(field, "input-field--danger");
}

void set_field_success_style(GtkWidget *field)
{
    remove_class(field, "input-field--danger");
    add_class(field, "input-field--success");
}

void set_notify_error_style( GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify-label--success");
    add_class(notify_label, "notify-label--danger");
    gtk_label_set_text(GTK_LABEL(notify_label), message);
}

void set_notify_success_style( GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify-label--danger");
    add_class(notify_label, "notify-label--success");
    gtk_label_set_text(GTK_LABEL(notify_label), message);
}

void clear_container(GtkWidget *container)
{
    gtk_container_foreach(GTK_CONTAINER(container), (GtkCallback)gtk_widget_destroy, NULL);
}

//return NULL if find nothing
GtkWidget *get_widget_by_name(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; 
    GList *children = NULL;

    if (GTK_IS_CONTAINER(container))
    {
        children = gtk_container_get_children(GTK_CONTAINER(container));
    }
    else {
        return NULL;
    }

    while (children)
    {
        if (!mx_strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data);
            break;
        }
        
        children = children->next;   
    }
    g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); //

    return result;
}

//return NULL if find nothing
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; 
    GList *children = NULL;

    if (GTK_IS_CONTAINER(container))
    {
        children = gtk_container_get_children(GTK_CONTAINER(container));
    }
    else
    {
        return NULL;
    }

    while (children)
    {
        if (!mx_strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data);
            break;
        }
        else if(GTK_IS_CONTAINER(children->data))
        {
            result = get_widget_by_name_r(children->data, name);
            if (result != NULL)
                break;
        }

        children = children->next;   
    }
    g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); //

    return result;
}

char *ellipsis_str(const char *str, int overflow_len)
{
    char *tmp = NULL;
    char *result = NULL;

    if (mx_strlen(str) >= overflow_len)
    {
        tmp = mx_strndup(str, overflow_len);
        result = mx_strjoin(tmp, "...");
        mx_strdel(&tmp);
    }
    else
    {
        result = mx_strdup(str);
    }

    return result;
}
