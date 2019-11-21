"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = require("express");
const DocumentController_1 = __importDefault(require("../controllers/DocumentController"));
class HomeRoutes {
    constructor() {
        this.router = express_1.Router();
        this.config();
    }
    config() {
        this.router.post("/files", DocumentController_1.default.receive);
        this.router.get("/get/file/:filename", DocumentController_1.default.getFile);
    }
}
const DocumentsRouter = new HomeRoutes();
exports.default = DocumentsRouter.router;
