import ScreenReactive
import RainbowAll
import Bridge
import sys


def print_logo(easter_egg_on):
    """
    This function is for printing out our lovely GUI title.

    @param{bool} Want easteregg? set as true
    @returns {void}
    """
    if not easter_egg_on:
        print(" █████╗ ██╗     ██╗     ██████╗ ███████╗██████╗ ██╗██████╗ ██╗  ██╗███████╗██████╗  █████╗ ██╗     ███████╗")
        print("██╔══██╗██║     ██║     ██╔══██╗██╔════╝██╔══██╗██║██╔══██╗██║  ██║██╔════╝██╔══██╗██╔══██╗██║     ██╔════╝")
        print("███████║██║     ██║     ██████╔╝█████╗  ██████╔╝██║██████╔╝███████║█████╗  ██████╔╝███████║██║     ███████╗")
        print("██╔══██║██║     ██║     ██╔═══╝ ██╔══╝  ██╔══██╗██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗██╔══██║██║     ╚════██║")
        print("██║  ██║███████╗███████╗██║     ███████╗██║  ██║██║██║     ██║  ██║███████╗██║  ██║██║  ██║███████╗███████║")
        print("╚═╝  ╚═╝╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝")
        print("                                                                                    MacOS PythonSide Script")
        print("                                                                                              By Gooday2die")
        print("                                      Please Check My Github : https://github.com/gooday2die/AllPeripherals")

    else:
        print(" ▄▄▄       ██▓     ██▓     ██▓███  ▓█████  ██▀███   ██▓ ██▓███   ██░ ██ ▓█████  ██▀███   ▄▄▄       ██▓      ██████ ")
        print("▒████▄    ▓██▒    ▓██▒    ▓██░  ██▒▓█   ▀ ▓██ ▒ ██▒▓██▒▓██░  ██▒▓██░ ██▒▓█   ▀ ▓██ ▒ ██▒▒████▄    ▓██▒    ▒██    ▒ ")
        print("▒██  ▀█▄  ▒██░    ▒██░    ▓██░ ██▓▒▒███   ▓██ ░▄█ ▒▒██▒▓██░ ██▓▒▒██▀▀██░▒███   ▓██ ░▄█ ▒▒██  ▀█▄  ▒██░    ░ ▓██▄   ")
        print("░██▄▄▄▄██ ▒██░    ▒██░    ▒██▄█▓▒ ▒▒▓█  ▄ ▒██▀▀█▄  ░██░▒██▄█▓▒ ▒░▓█ ░██ ▒▓█  ▄ ▒██▀▀█▄  ░██▄▄▄▄██ ▒██░      ▒   ██▒")
        print(" ▓█   ▓██▒░██████▒░██████▒▒██▒ ░  ░░▒████▒░██▓ ▒██▒░██░▒██▒ ░  ░░▓█▒░██▓░▒████▒░██▓ ▒██▒ ▓█   ▓██▒░██████▒▒██████▒▒")
        print(" ▒▒   ▓▒█░░ ▒░▓  ░░ ▒░▓  ░▒▓▒░ ░  ░░░ ▒░ ░░ ▒▓ ░▒▓░░▓  ▒▓▒░ ░  ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ▒░▓  ░▒ ▒▓▒ ▒ ░")
        print("  ▒   ▒▒ ░░ ░ ▒  ░░ ░ ▒  ░░▒ ░      ░ ░  ░  ░▒ ░ ▒░ ▒ ░░▒ ░      ▒ ░▒░ ░ ░ ░  ░  ░▒ ░ ▒░  ▒   ▒▒ ░░ ░ ▒  ░░ ░▒  ░ ░")
        print("  ░   ▒     ░ ░     ░ ░   ░░          ░     ░░   ░  ▒ ░░░        ░  ░░ ░   ░     ░░   ░   ░   ▒     ░ ░   ░  ░  ░  ")
        print("      ░  ░    ░  ░    ░  ░            ░  ░   ░      ░            ░  ░  ░   ░  ░   ░           ░  ░    ░  ░      ░  ")
        print("                                                                                            MacOS PythonSide Script")
        print("                                                                                                      By Gooday2die")
        print("                                              Please Check My Github : https://github.com/gooday2die/AllPeripherals")


def parse_argv():
    """
    This function is for pasring argvs from system call.
    The argv call would be in this format

    python3 main.py -easteregg true -operationmode 1

    @param {void}
    @returns {list} list of argvs
    """
    argv_list = sys.argv
    return_params = list()

    positive = ['True', 'true', 'on', 'ON', 'On']
    valid_op_mode = [1, 2]

    # Operation mode 1 : Screen reactive
    # Operation mode 2 : Rainbow All
    # Others : not implemented yet...

    easter_egg_param = bool()
    operation_mode_param = int()

    if len(argv_list) < 2:  # When we do not have any params
        pass

    elif '-help' in argv_list:  # When we entered help param
        print("Please check PARAMETERS.txt in this directory")
        exit(0)

    else:  # When we have parameters
        try:
            easter_egg_index = argv_list.index("-easteregg")
            easter_egg_param = argv_list[easter_egg_index + 1] in positive

            operation_mode_index = argv_list.index("-operationmode")
            operation_mode_param = int(argv_list[operation_mode_index + 1])

            if operation_mode_param not in valid_op_mode:
                print("[ERROR] Invalid operation mode")
                exit(0)
        except:
            pass

    return_params.append(easter_egg_param)
    return_params.append(operation_mode_param)

    return return_params


def screen_reactive():
    """
    This function is for doing all the screen reactive jobs in one function
    @param {void}
    @returns {void}
    """
    bridge_obj = Bridge.Bridge(1)
    screen_reactive_obj = ScreenReactive.ScreenReactive()

    while True:
        rgb_list = screen_reactive_obj.return_rgb()
        bridge_obj.send_rgb_value(rgb_list[0], rgb_list[1], rgb_list[2])


def rainbow_all():
    """
    This function is for doing all the rainbow all jobs in one function
    @param {void}
    @returns {void}
    """
    bridge_obj = Bridge.Bridge(2)

    while True:  # This part is for error and exception detection.
        try:
            #speed = float(input("Speed (default 0.005) : "))
            speed = 0.005
            break

        except ValueError:  # if someone types 12swergw as input...
            pass

    rainbow_obj = RainbowAll.RainbowAll(bridge_obj, speed)
    rainbow_obj.rainbow_all()


if __name__ == "__main__":
    params = parse_argv()
    print(params)

    print_logo(params[0])


    if params[1] == 1:
        print("[OperationMode] Set Operation Mode 1 : Screen Reactive")
        screen_reactive()

    elif params[1] == 2:
        print("[OperationMode] Set Operation Mode 2 : Rainbow All")
        rainbow_all()

    else:  # Called this script without parmeters
        print("Please Select Operation Mode")
        print("1 ScreenReactive")
        print("2 RainbowAll")

        while True:
            try:
                op_mode = int(input("Mode : "))
                break
            except ValueError:
                pass

        if op_mode == 1:
            print("[OperationMode] Set Operation Mode 1 : Screen Reactive")
            screen_reactive()

        elif op_mode == 2:
            print("[OperationMode] Set Operation Mode 2 : Rainbow All")
            rainbow_all()

        else:
            print("[ERROR] Not implemented")
            exit(0)
