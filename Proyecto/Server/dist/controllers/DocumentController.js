"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class DocumentController {
    receive(req, res) {
        const re = req;
        const files_names = new Array();
        for (const name of re.files) {
            files_names.push(name.filename);
        }
        res.json({ status: "success", err: {}, data: { info: files_names } });
    }
}
const documentController = new DocumentController();
exports.default = documentController;
