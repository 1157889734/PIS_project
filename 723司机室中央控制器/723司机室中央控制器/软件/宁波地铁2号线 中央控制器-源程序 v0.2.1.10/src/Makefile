CC = arm-linux-g++
CFLAGS = -O2 -Wall -g
#CFLAGS = -O2 -Wall
LDFLAGS="-L/opt/temp/ffmpeg/lib"
#CFLAGS = "-I/opt/temp/ffmpeg/include"
TOP_DIR = ..
INSTALL_DIR = /bin
PROJECT = Pisc.axf
DEBUG_DIR = /debug

#source

#User
SOURCE  = User/main.c

#lib
SOURCE  += lib/print.c
SOURCE  += lib/standard_file.c
SOURCE  += lib/ini_file.c
SOURCE  += lib/checksum.c
SOURCE  += lib/crc16.c
SOURCE  += lib/utils.c
SOURCE  += lib/xor.c
SOURCE  += lib/pisc_pack.c
SOURCE  += lib/mutex.cpp
SOURCE  += lib/thread.cpp


#driver
#SOURCE  += driver/driver.c
SOURCE  += driver/soundcard.c
SOURCE  += driver/led.c


#port_layer
SOURCE  += port_layer/ctrl_port.c
SOURCE  += port_layer/fep_audio_port.c
SOURCE  += port_layer/broadcast_audio_port.c
SOURCE  += port_layer/io.c


#operate_device
SOURCE  += operate_device/pisc.c
SOURCE  += operate_device/dcp.c
SOURCE  += operate_device/tms.c
SOURCE  += operate_device/occ.c
SOURCE  += operate_device/ptu.c

#terminal_device
SOURCE  += terminal_device/dva.c
SOURCE  += terminal_device/media.c
SOURCE  += terminal_device/pisc_local.c
SOURCE  += terminal_device/recon.c
SOURCE  += terminal_device/lcu_led.c
SOURCE  += terminal_device/head_led.c
SOURCE  += terminal_device/dmp.c


#process_matrix
SOURCE  += process_matrix/data_proc_matrix.c
SOURCE  += process_matrix/io_proc_matrix.c

#manage
SOURCE  += manage/dev_status.c
SOURCE  += manage/log.c
SOURCE  += manage/broadcast.c
SOURCE  += manage/master.c
SOURCE  += manage/sys.c
SOURCE  += manage/dva_broadcast_rule.c
SOURCE  += manage/mp3_decoder.c
SOURCE  += manage/train_manage.c
SOURCE  += manage/io_manage.c
SOURCE  += manage/debug_info_manage.c

#LDFLAGS="-L/opt/crosstool/gcc-4.1.0-glibc-2.3.2/arm-linux/arm-linux/lib"
#LDFLAGS="-L/opt/EmbedSky/4.3.3/arm-none-linux-gnueabi/libc/armv4t/usr/lib"


#make

SUBDIRS := $(shell find -type d)

#$(shell mkdir -p $(TOP_DIR)$(INSTALL_DIR))

$(shell for val in $(SUBDIRS);do \
mkdir -p $(TOP_DIR)$(INSTALL_DIR)/$${val}; \
done;)

OBJS = $(SOURCE:%.c=$(TOP_DIR)$(INSTALL_DIR)/%.o)

$(TOP_DIR)$(INSTALL_DIR)/%o:%c

$(TOP_DIR)$(INSTALL_DIR)/$(PROJECT):$(OBJS) $(HEADERS)
#$(TOP_DIR)$(INSTALL_DIR)/$(PROJECT):$(TOP_DIR)$(INSTALL_DIR)/%.o $(HEADERS)
#	$(CC) $(CFLAGS) -o $@ $^ -lpthread --static
	$(CC) $(CFLAGS) -o $@ $^ -lavformat -lavcodec -lavutil -lm -lpthread  -lz --static
#	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread --static

$(TOP_DIR)$(INSTALL_DIR)/%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

install:
	cp $(TOP_DIR)$(INSTALL_DIR)/$(PROJECT) /home/zhong/nfs_dir/

############################################################
debug:
#$(TOP_DIR)$(INSTALL_DIR)/%o:%c

#$(TOP_DIR)$(INSTALL_DIR)/$(PROJECT):$(OBJS) $(HEADERS)
#	$(CC) $(CFLAGS) -o $@ $^ -lpthread -g

#$(TOP_DIR)$(INSTALL_DIR)/%.o:%.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@
	arm-linux-insight $(TOP_DIR)$(INSTALL_DIR)/$(PROJECT)
#	insight $(TOP_DIR)$(INSTALL_DIR)/$(PROJECT)
#	ddd -debugger arm-linux-gdb $(TOP_DIR)$(INSTALL_DIR)/$(PROJECT)

############################################################
clean:
	-rm -rf $(TOP_DIR)$(INSTALL_DIR)
test:
	insight $(TOP_DIR)$(INSTALL_DIR)/$(PROJECT)
