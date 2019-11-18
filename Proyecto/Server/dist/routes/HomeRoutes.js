"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = require("express");
const homeController_1 = __importDefault(require("../controllers/homeController"));
class HomeRoutes {
    constructor() {
        this.router = express_1.Router();
        this.config();
    }
    config() {
        this.router.get("/", homeController_1.default.index);
    }
}
const homeRoutes = new HomeRoutes();
exports.default = homeRoutes.router;
