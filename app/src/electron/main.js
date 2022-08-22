const { app } = require('electron');
const electronBrowserWindow = require('electron').BrowserWindow;
const electronDialog = require('electron').dialog;
const electronIpcMain = require('electron').ipcMain;

const fs = require('fs');

const nodePath = require("path");

const { Menu } = require('electron');

const Store = require('electron-store');
const { fstat } = require('fs');

const store = new Store('project');

let window;

const menuTemplate = [
    {
        label: 'Help',
        submenu: [
            {
                label: 'Help',
                click: () => {
                    window.loadFile('./views/discord.html');
                }
            }
        ]
    }
];

//Creates Main Window
function createMainWindow() {
    const mainWindow = new electronBrowserWindow({
        width: 900,
        height: 600,
        show: false,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: nodePath.join(__dirname, 'preload.js')
        }
    });

    mainWindow.loadFile('index.html')
        .then(() => { mainWindow.show(); });

    return mainWindow;
}
//Creates the Discord Window
function createDiscordWindow() {
    const discordWindow = new electronBrowserWindow({
        width: 450 * 1.5, 
        height: 300 * 1.5,
        show: false,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: nodePath.join(__dirname, 'preload.js')
        }
    });

    discordWindow.loadFile('./views/discord.html')
        .then(() => { discordWindow.show(); });

    return discordWindow;
}

//App Ready/Done Stuff
app.on('ready', () => {
    mainWindow = createMainWindow();
    if(store.get("discordbtnclicked") != "clicked"){
        discordWindow = createDiscordWindow();
    }

    //Menu.setApplicationMenu(null);
});
//If all windows are closed
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    if (electronBrowserWindow.getAllWindows().length === 0) {
        mainWindow = createMainWindow();
        if(store.get("discordbtnclicked") != "clicked"){
            discordWindow = createDiscordWindow();
        }

        Menu.setApplicationMenu(null);
    }
});

//Opens the Emulator
function openEmu() {   

    const emulatorWindow = new electronBrowserWindow({
        width: 256 + 21, 
        height: 192 * 2 + 75,
        show: false,
        resizable: false,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: nodePath.join(__dirname, 'preload.js')
        }
    });

    emulatorWindow.loadFile('./views/Emulator.html')
        .then(() => { emulatorWindow.show(); });
    return emulatorWindow;
}

// Let's listen for a call on the 'getPath' channel
electronIpcMain.handle('getPath', async () => {
    // Dialog options.
    const options = {
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj", "JSON"],
            }
        ]
    }

    // When available, return the modified path back to the render thread via IPC
    return await openDialog(mainWindow, options)
        .then((result) => {
            // User cancelled the dialog
            if (result.canceled === true) { return; }

            let path = result.filePaths[0];

            if(result.canceled === true){
                return result.canceled;
            }
            else{
                store.set('ProjectDir', nodePath.parse(path).dir);
                return path;
            }
        })
})

function openDialog(parentWindow, options) {
    return electronDialog.showOpenDialog(parentWindow, options)
        .then((result) => { if (result) { return result; } })
        .catch((error) => { console.error('Show open dialog error: ' + error); });
}

electronIpcMain.handle('openEmu', async () => {
    emulatorWindow = openEmu();
})

electronIpcMain.handle('OpenDocs', async () => {
    require('electron').shell.openExternal('https://bowersindustry.github.io/ds-creator-docs/');
})