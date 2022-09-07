/// Overwrite console.log method to tell apart emulator logs from the rest of the messages.

var nds_log_feedback = function(msg) {
	alert(msg);
};

console.log = (function() {
	var original_log = console.log;	
	
	return function(...args) {				
		if(args.length==1 && (typeof args[0] === 'string' || args[0] instanceof String)) {
			if(args[0].startsWith("[EMU|LOG] << ")) {
				var nds_log_message = args[0].substring(13);
				// ^-- the extracted log message
				// use it in the emu window, or send it to main window
				nds_log_feedback(nds_log_message);
				return;
			}
		}
		original_log(...args);
	}
})();