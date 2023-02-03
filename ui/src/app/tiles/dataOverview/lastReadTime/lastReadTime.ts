import { Service } from 'src/shared/service';
import { Component } from "@angular/core";

@Component({
    selector: "lastReadTimeComponent",
    templateUrl: "./lastReadTime.html"
})
export class LastReadTimeComponent {
    public timestamp: string;

    constructor(
        private service: Service
    ) { }

    ngOnInit() {
        this.service.latestData.subscribe(data => {
            this.timestamp = data.timestamp
        })
    }
}