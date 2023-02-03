export const DEFAULT_BAR_CHART_OPTIONS = {
    data: {
        datasets: [],
        labels: [],
    },
    options: {
        elements: {
            point: {
                radius: 0
            }
        },
        plugins: {
            legend: {
                position: 'bottom',
            },
            tooltip: { callbacks: {} }
        },
        scales: {
            y: {
                offset: true,
            },
            y2: {
                offset: true,
                position: 'right',
                grid: {
                    drawOnChartArea: false, // only want the grid lines for one axis to show up
                },
            },
        },
        responsive: true,
    }
}