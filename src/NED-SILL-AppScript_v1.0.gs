/**
 * NED-SILL — Google Sheets Logging AppScript
 * Version: 1.0
 *
 * Google Apps Script for receiving real-time liquid level
 * data from NED-SILL devices via HTTP GET requests and
 * logging timestamped readings with multi-unit conversion
 * (feet, inches, cm) and tank level labels to Google Sheets.
 *
 * Deploy as: Web App → Execute as Me → Access: Anyone
 *
 * Data received per request:
 *   value0 = distance in feet (from ESP8266 firmware)
 *
 * Columns logged:
 *   1. Timestamp (Asia/Karachi timezone)
 *   2. Level (feet)
 *   3. Level (inches)
 *   4. Level (cm)
 *   5. Status label (Full / Almost Full / Half / Empty etc.)
 *
 * Author:  Humayun Khan
 * Lab:     HHRCM Lab, NCRA-NEDUET, Karachi, Pakistan
 * Mentor:  Prof. Dr. Riaz Uddin (Director NCRA & ORIC, NEDUET)
 * Patent:  IPO Pakistan (Under Review)
 *
 * CONFIGURATION:
 * Replace sheet_id with your own Google Sheets ID.
 *
 * © 2025 Humayun Khan, HHRCM Lab NCRA-NEDUET
 */

function doGet(e) {
  Logger.log(JSON.stringify(e));

  var result = 'Ok';

  if (Object.keys(e.parameter).length === 0) {
    return ContentService.createTextOutput('No Parameters');
  }

  // --- CONFIGURATION ---
  var sheet_id = 'YOUR_GOOGLE_SHEET_ID'; // Replace before deployment
  // ---------------------

  var sheet   = SpreadsheetApp.openById(sheet_id).getActiveSheet();
  var newRow  = sheet.getLastRow() + 1;
  var rowData = [];

  // Timestamp (Asia/Karachi)
  var now       = new Date();
  var timestamp = Utilities.formatDate(now, "Asia/Karachi", 'yyyy-MM-dd HH:mm:ss');
  rowData.push(timestamp);

  // Parse distance in feet
  var levelFeet = parseFloat(e.parameter.value0);
  if (isNaN(levelFeet)) {
    return ContentService.createTextOutput('Invalid parameter: value0');
  }

  // Unit conversions
  var levelInches = levelFeet * 12;
  var levelCm     = levelInches * 2.54;

  rowData.push(levelFeet);
  rowData.push(levelInches.toFixed(2));
  rowData.push(levelCm.toFixed(2));

  // Tank level label based on distance from sensor (top of tank)
  // Distance increases as tank empties
  var label = levelFeet <= 3    ? "Full"
            : levelFeet <= 5    ? "Almost Full"
            : levelFeet <= 8    ? "Almost Half"
            : levelFeet <= 11   ? "Half"
            : levelFeet <= 14   ? "Less than Half"
            : levelFeet <= 17   ? "Almost Empty"
            : levelFeet <= 19.6 ? "Empty"
            : "Out of Range";

  rowData.push(label);

  Logger.log(JSON.stringify(rowData));

  // Write to sheet
  sheet.getRange(newRow, 1, 1, rowData.length).setValues([rowData]);

  return ContentService.createTextOutput(result);
}
