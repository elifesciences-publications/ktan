#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <gtkmm.h>
#include "rhd2000evalboard.h"
#include "acquisition.h"
#include "recording.h"
#include "timeKeeper.h"
#include "dataBuffer.h"


class mainWindow: public Gtk::Window
{
 private:
  acquisition* acq;
  dataBuffer* db; // data buffer not deutsche bahn
  recording* rec;
  pthread_t acquisition_thread;
  int acquisition_thread_id;
  pthread_t recording_thread;
  int recording_thread_id;
  int num_channels;
  
 public:
  mainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);//constructor
  virtual ~mainWindow();
  
 protected:
  Glib::RefPtr<Gtk::Builder> builder;

  // widgets
  Gtk::ToggleToolButton* play_toolbutton;
  Gtk::ToggleToolButton* record_toolbutton;
  sigc::connection record_toolbutton_connection;
  Gtk::ToolButton*  rewind_toolbutton;
  Gtk::ToolButton*  forward_toolbutton;
  Gtk::ToolButton*  gain_increase_toolbutton;
  Gtk::ToolButton*  gain_decrease_toolbutton;
  Gtk::ToolButton*  time_increase_toolbutton;
  Gtk::ToolButton*  time_decrease_toolbutton;
  Gtk::ToolButton*  add_toolbutton;
  Gtk::ToolButton*  remove_toolbutton;

  Gtk::MenuItem* about_menuitem;
  Gtk::MenuItem* quit_menuitem;
  Gtk::MenuItem* oscilloscope_menuitem;
  Gtk::MenuItem* recording_menuitem;

  Gtk::AboutDialog* about_dialog;
  Gtk::Dialog* recording_dialog;
  Gtk::Dialog* oscilloscope_dialog;

  Gtk::TreeView* recording_treeview;
  Gtk::SpinButton* trial_spinbutton;
  Gtk::Entry* file_name_entry;
  Gtk::Statusbar* statusbar;

  string date_string;
  /* GtkWidget *window;  // main window */
  /* GtkWidget *vbox1; // main vbox in the main window, to put the gtkdatabox */
  /* GtkWidget *test_label; */
  /* GtkWidget *drawing_area; */
  /* GdkColor color; */
  /* GtkAdjustment *sampling_rate_adjustment; */
  /* GtkAdjustment *osc_group_adjustment; */
  /* GtkAdjustment *osc_group_preferences_adjustment; */
  /* GtkAdjustment *trial_no_adjustment; */
  /* GtkWidget *about_dlg; // about dialog */
  /* GtkWidget *acquisition_dlg; */
  /* GtkWidget *oscilloscope_dlg; */
  /* GtkWidget *recording_dlg; */
  /* GtkWidget *toolbar; */
  /* GtkWidget *dev1_name_label; // to show user the name of device */
  /* GtkWidget *dev2_name_label; // to show user the driver */
  /* GtkWidget *dev1_driver_label; */
  /* GtkWidget *dev2_driver_label; */
  /* GtkWidget *num_devices_detected_label; */
  /* GtkWidget *sampling_rate_value_label; */
  /* GtkWidget *num_available_channels_label; */
  /* GtkWidget *num_channels_device_1_label; */
  /* GtkWidget *num_channels_device_2_label; */
  /* GtkWidget *range_label; */
  /* GtkWidget *current_saving_directory_label2; */
  /* GtkWidget *group_preferences_spinbutton; */
  /* GtkWidget *preferences_channel_vbox; // to display the channel information */
  /* GtkWidget *file_name_entry; // filebase of the file name */
  /* GtkWidget *trial_spinbutton; // index following filebase for file name */
  /* GtkWidget *statusbar; // index following filebase for file name    */
  /* GtkWidget *group_spinbutton; // for oscilloscope display group */
  /* GtkWidget *recording_channel_view; // treeview to select the channels to record */
  /* GtkWidget *time_decrease_image; */
  /* GtkWidget *time_increase_image; */
  /* GtkWidget *gain_decrease_image; */
  /* GtkWidget *gain_increase_image; */
  /* GtkWidget *time_decrease_toolbutton; */
  /* GtkWidget *time_increase_toolbutton; */
  /* GtkWidget *gain_decrease_toolbutton; */
  /* GtkWidget *gain_increase_toolbutton; */

  /* GtkListStore  *recording_channel_store; //to fill up the treeview to select the recording channels */
  /* GtkWidget *oscilloscope_all_channels_view; // treeview to select the channels to record */
  /* GtkListStore  *oscilloscope_all_channels_store; // to fill the treeview to select the channels for oscilloscope */
  /* GtkWidget *oscilloscope_selected_channels_view; // selected channels for a page of the oscilloscope */
  /* GtkListStore *oscilloscope_selected_channels_store; // to fill the treeview for a group of the oscilloscope */
  /* int is_filling_selected_channel_liststore; */



  //Tree model columns:
  class ModelRecordingColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelRecordingColumns()
    { add(m_col_id); add(m_col_name); add(m_col_selected);}
    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<bool> m_col_selected;
  };
  ModelRecordingColumns m_RecordingColumns;
  Glib::RefPtr<Gtk::ListStore> m_refRecTreeModel;

  // callback functions
  void on_play_toolbutton_toggled();
  void on_record_toolbutton_toggled();
  void on_rewind_toolbutton_clicked();
  void on_forward_toolbutton_clicked();
  void on_gain_increase_toolbutton_clicked();
  void on_gain_decrease_toolbutton_clicked();
  void on_time_increase_toolbutton_clicked();
  void on_time_decrease_toolbutton_clicked();
  void on_add_toolbutton_clicked();
  void on_remove_toolbutton_clicked();
  void on_about_menuitem_activate();
  void on_quit_menuitem_activate();
  void on_oscilloscope_menuitem_activate();
  void on_recording_menuitem_activate();
  void change_recording_treeview_selection(bool sel);
  void update_recording_channels();
  string get_file_name_from_window();
  void build_model_recording_treeview();
  bool check_file_overwrite();
  void set_date_string();
};

#endif // MAINWINDOW_H
